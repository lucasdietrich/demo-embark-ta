//! Example using the `myta` wrapper.

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut value: u32 = 42;
    if let Some(arg) = std::env::args().nth(1) {
        value = arg.parse()?;
    }

    let mut session = myta::Session::open()?;

    println!("Invoking TA to increment {value}");
    value = session.inc_value(value)?;
    println!("TA incremented value to {value}");

    Ok(())
}
