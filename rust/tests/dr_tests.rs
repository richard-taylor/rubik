use rc::cube;

#[test]
fn is_solved() {
    assert!(cube::solved());
}

#[test]
fn can_run() {
    rc::run("R U F", "solved")
}