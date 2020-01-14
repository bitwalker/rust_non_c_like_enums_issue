#[derive(Clone, Copy)]
#[repr(u32)]
pub enum Type {
    Unknown,
    Tuple(u32),
}

#[derive(Clone, Copy)]
#[repr(C, u32)]
pub enum Type2 {
    Unknown,
    Tuple(u32),
}

extern "C" {
    pub fn RunTest1(ty: Type) -> bool;
    pub fn RunTest2(ty: Type2) -> bool;
    pub fn RunTest3(ty: *const Type) -> bool;
    pub fn RunTest4(ty: *const Type2) -> bool;
}

pub fn main() -> Result<(), &'static str> {
  let t = Type::Tuple(1);
  let t2 = Type2::Tuple(2);
  let mut success = true;
  success &= run_test(1, || unsafe { RunTest1(t) });
  success &= run_test(2, || unsafe { RunTest2(t2) });
  success &= run_test(3, || unsafe { RunTest3(&t) });
  success &= run_test(4, || unsafe { RunTest4(&t2) });

  if success {
      return Ok(());
  }
  
  Err("Tests failed!")
}

fn run_test<T>(test_name: usize, test: T) -> bool 
where
    T: Fn() -> bool,
{
    print!("Running test {}..", test_name);
    let result = test();
    if result {
        println!("passed");
    } else {
        println!("failed");
    }

    result
}
