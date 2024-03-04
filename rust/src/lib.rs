pub mod cube;

use clap::Parser;

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    /// A scramble to solve e.g. "R U R' F L D2 B"
    #[arg(short, long, default_value="")]
    scramble: String,

    /// A pattern to find from the scrambled state e.g. "2x2x2"
    #[arg(short, long, default_value="solved")]
    pattern: String,

    /// Number of times to greet
    #[arg(short, long, default_value_t = 1)]
    count: u8,
}

pub fn main() {
    let args = Args::parse();

    run(&args.scramble, &args.pattern)
}

pub fn run(scramble: &str, pattern: &str) {

}