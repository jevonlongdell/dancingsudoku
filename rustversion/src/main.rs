use std::{fs::File};
use std::io::prelude::*;
use std::path::Path;
use std::io::{Error, ErrorKind};
use std::io::BufReader;


const P_SIZE_RT: usize = 3;
const P_SIZE: usize =  P_SIZE_RT * P_SIZE_RT;
const P_SIZE_SQ: usize = P_SIZE*P_SIZE;




#[derive(Debug)]
struct Node{
    left: usize, //index (not pointer) of the node to the left
    right: usize, //index (not pointer) of the node to the right (it wraps around at the end)
    up: usize,
    down: usize,
    colsize: Option<usize>,
    colidx: usize
}




// reads in a puzzle description from a text file
// returns is at as an 81 element array of u8's
// if the value is unknown it records that as a zero
// if it reads a char that is not a digit or '.' then it 
// it simply ignores it and reads another
fn read_in_puzzle_desc( f: &mut BufReader<File>) -> Result<([u8; P_SIZE_SQ]),std::io::Error> {
    let mut sudoku: [u8; P_SIZE_SQ] = [0; P_SIZE_SQ];
    let mut chbuf = [0;1]; 
   
    for cell in sudoku.iter_mut() {
        loop{
            //println!("reading char");
            let n = f.read(&mut chbuf[..]).unwrap();//.expect("problem reading from file");
            //println!("{:?}", chbuf[0] as char);
            if n==0 {
                return Err(Error::new(ErrorKind::Other,"ran out of bytes"));
            }
            let ch = chbuf[0];
            if (ch>='0' as u8) && ch<='9' as u8{
                 *cell = ch - ('0' as u8);
                 break;   
             }
            if ch==('.' as u8) {
                *cell = 0;
                break;
            }

        }
    }
    Ok(sudoku)
}



fn hidenode(n: usize, m: &mut Vec<Node>) {
    println!("Hiding node {}",n);
    let l = m[n].left;
    let r = m[n].right;
    println!("{} {:?}",n,m[n]);
    println!("L {} {:?}",l,m[l]);
    println!("R {} {:?}",r,m[r]);
    
    //assert_ne!(l,r);
    m[l].right = r; 
    m[r].left = l; 
}


fn unhidenode(n: usize, m: &mut Vec<Node>) {
    let l = m[n].left;
    let r = m[n].right;
    //assert_ne!(l,r);
    m[l].right = n; 
    m[r].left = n; 
}



fn hidecolumn (col: usize, m: &mut Vec<Node>){
    let mut n = col;
//    println!("Column is {}",n);
//    let mut count=0;
    loop{
//	println!("n = {}",n);
        hidenode(n, m);
        n = m[n].down;
//	println!("n = {}",n);
        if n==col{
//	   println!("This column is done");
            break;
        }
//        count+=1;
//        assert!(count<5);
    }

}

fn unhidecolumn (col: usize, m: &mut Vec<Node>){
    let n = col;
    loop{
        unhidenode(n,  m);
        let n = m[n].down;
        if n==col{
            break;
        }
    }

}







//print out human readible puzzle description
fn print_puzzle_desc(s: [u8; P_SIZE_SQ]){
    for (i,val) in s.iter().enumerate(){
        if *val == 0  {
            print!(". ");
        } else {
            print!("{} ",val);
        }
        if i% P_SIZE == (P_SIZE-1) {
            println!();
        }
    }
}



fn main() {

    let filepath = Path::new("all_17_clue_sudokus.txt");

    let file = match File::open(&filepath) {
        Err(why) => panic!("Couldn't open file {}, {}",filepath.display(),why),
        Ok(f) => f,
    };
    
    let mut f = BufReader::new(file);

    let mut s = String::new();
    f.read_line(&mut s).unwrap();
    let num_puzzles: usize = s.trim().parse().unwrap();
    //for _k in 0..1{//num_puzzles
    let p =  read_in_puzzle_desc(&mut f).unwrap();

        // for k in 0..9 {
        //     for j in 0..9{
        //         if p[k+9*j]!=0{
        //             let mut row
        //         }




    //let p = sovle_sudoku(p);
        print_puzzle_desc(p);
        println!();
    //}

    let mut m =  Vec::<Node>::new();

    let mut soln = Vec::<usize>::new(); // the solution are stored by recording the index of a node
                                    // in that row

    //push on the column headers
    for k  in  0..(4* P_SIZE_SQ as i32) {
        let n = Node{
            left: ((k-1)%(4* P_SIZE_SQ as i32)) as usize,
            right:((k+1)%(4*P_SIZE_SQ as i32)) as usize,
            up:k as usize,
            down:k as usize,
            colsize: Some(0),
            colidx: k as usize
            };
        m.push(n);
    }
    let mut num_given_rows=0;

    for puzrow in 0..9{
        for puzcol in 0..9{
            let digit = p[puzrow+9*puzcol] as usize;
            if digit != 0{
                num_given_rows=num_given_rows+1;
                let puzbox = (puzrow%3) + 3*(puzcol%3);
                let cols: [usize;4] = [ puzrow+9*puzcol, //we'll put a 1 in this column of matrix to ensure that there is only one digit in this square
                                       81 + puzrow + 9*digit,  // we'll put a 1 in the column of matrix to ensure that there is only of this digit in this row
                                     2*81 + puzcol + 9*digit,
                                     3*81 + puzbox + 9*digit];
                let k = m.len();
                soln.push(k);
                for (i, c) in cols.iter().enumerate(){
                    let n = Node{
                        left: k + (3+i)%4,
                        right:k + (1+i)%4,
                        up:m[*c].up,
                        down:*c,
                        colsize: None,
                        colidx: *c
                    };
                    m[*c].colsize.map(|x| x+1);
                    let oldbottom = m[*c].up;// old bottom of column
                    m[oldbottom].down=k+i;
                    m[*c].up = k+i;
                    m.push(n);
                    println!("{} {:?}",k+i, m[k+i]);
                    println!("{} {:?}",*c, m[*c]);
                    
                }
            }
        }
    }

    for puzrow in 0..9{
        for puzcol in 0..9{
            if p[puzrow+9*puzcol] ==0 {
                for digit in 0..9 {
                    let puzbox = (puzrow%3) + 3*(puzcol%3);
                    let cols: [usize;4] = [ puzrow+9*puzcol, //we'll put a 1 in this column of matrix to ensure that there is only one digit in this square
                                           81 + puzrow + 9*digit,  // we'll put a 1 in the column of matrix to ensure that there is only of this digit in this row
                                         2*81 + puzcol + 9*digit,
                                         3*81 + puzbox + 9*digit];
                    let k = m.len();
                    for (i, c) in cols.iter().enumerate(){
                        let n = Node{
                            left: k + (3+i)%4,
                            right:k + (1+i)%4,
                            up:m[*c].up,
                            down:*c,
                            colsize: None,
                            colidx: *c
                        };
                        m[*c].colsize.map(|x| x+1);
                        let oldbottom = m[*c].up;// old bottom of column
                        m[oldbottom].down=k+i+1;
                        m[*c].up = k+i+1;
                        m.push(n);
                    }
                }
            }
        }
    }

    let root = m.len();
    let mut rootnode = Node{
        right: 0,
        left: 323,
        up: root,
        down: root,
        colsize: None,
        colidx: root 
    };
    m.push(rootnode);

    //lets solve this sucker
    println!("root = {}",root);

    //loop all the elements in the solution rows and hide
    // the corresponding columns

    for first_node_in_row in soln.iter() {
        let mut n = *first_node_in_row;
        let mut count = 0;
        loop {
            let col = m[n].colidx;
            hidecolumn(col, &mut m);
            n = m[n].right;
            if n==*first_node_in_row{
                break;
            }
            count+=1;
            assert!(count<10)
        }
    }





    println!("{}",m.len());
    println!("Hello, world!");
}