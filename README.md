# Table of Contents
1. [Project Description](./docs/project_description.md)
2. [User Stories](./docs/user_stories.md)
3. Design Diagrams
    - [Level 0](./docs/design_diagrams/D0.pdf)
    - [Level 1](./docs/design_diagrams/D1.pdf)
    - [Level 2](./docs/design_diagrams/D2.pdf)
4. Project Tasks and Timeline
    - [Task List](./docs/tasklist.md)
    - [Time Line](./docs/timeline.md)
5. [ABET Concerns Essay](./docs/essays/constraints-essay-gr.pdf)
6. [PPT Slideshow](./docs/presentations/Midterm_Presentation.pdf)
7. Self-Assessment Essays
    - [Team Contract](./docs/essays/team-contract-gr.pdf)
    - [Capstone Assessment](./docs/essays/capstone-assessment-gr.pdf)
8. [Professional Bio](./docs/bio_rodriguez.md)
9. [Budget](#budget)
10. [Appendix](#appendix)

### Note:
- Since this is a solo project, the *Effort Matrix* assignment was skipped. 

# Budget
- TBD

# Appendix
### During the devlepment of this project, the following two programming languages were considered due to their portability:
- Rust
- Python

### Python was chosen over Rust for the following reasons:
1. At the moment, Rust does not have an embedded framework equivalent to MicroPython. This means that code written for a given board could only work on the board in question. This would negatively impact the extensibilty of this project. Note that this is the **main reason** Python was chosen over Rust.
2. More documentation and tutorials for third-party packages exist for Python than Rust. For example, there are more references for aiomqtt (Python) and umqtt.simple (MicroPython) than there are for rumqttc (Rust) as of early Octover. However, the references for rumqttc seemed to have improved since then.
3. Python is simpler to learn and understand than Rust. This is due to Rust's very strict typing system and variable lifetime management. Rust's *borrow checker* could also prove difficult to understand for novice software developers. However, the features that make Rust difficult are also what make it safe and performant to program in.

### Here are some reasons that one could chose Rust over Python in the future:
1. If hosting Python proved to be expensive due to its lower performance when compared to Rust, then the extra difficulty of Rust could pay off in reduced expenses.
2. If a Rust embedded framework equivalent to MicroPython or Arduino were to be created, then new developers would only have to learn the basics of Rust. If training said developers is deemed low risk enough, then Rust would be a great way write safe and perfomant code. Note that as time goes on, the documentation for third-party Rust packages will likely continue to improve. This could make learning Rust even easier, thus lowering the risk associated with training developers on Rust.

### Source Code Overview
- To view the Rust code that was developed before being abandoned, refer to the [Rust](Rust/) folder.
- To view and try the Python code that is currently being developed, open the [Python](Python/) folder in VS Code and refer to the folder's [README](Python/README.md).

### Licensing
- This repo was licensed under the MIT license because it:
    1. Protects any related documenation
    2. Is compatible with the Rust and Python packages being used
    3. Would allow a company to freely use the data pipeline template that this repo will eventually outline