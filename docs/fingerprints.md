### TODO: Spell Check, many of these specs have obvious (English) typos

# Fingerprint Specifications

This is a reference for all the Funge-98 specifications that I could find.

Specifications can be found in the Markdown documents in the [fingerprints](fingerprints) folder.

Cat's Eye, RCS, and JVH fingerprints are separated into folders because there are multiple from those originators, others are at the top level of the folder.

The Mycology column indicates whether an extension is tested in Mycology.

| Implemented | Mycology | Name |  Fingerprint  |         Origin         | Description                             |
|:-----------:|:--------:|:----:|:-------------:|:----------------------:|:----------------------------------------|
|      ❌      |    ✅     | HRTI | `0x48525449`  | Cat's Eye Technologies | High-Resolution Timer Interface         |
|      ❌      |    ✅     | MODE | `0x4d4f4445`  | Cat's Eye Technologies | Funge-98 Standard Modes                 |
|      ❌      |    ✅     | MODU | `0x4d4f4455`  | Cat's Eye Technologies | Modulo Arithmetic Extension             |
|      ✅      |    ✅     | NULL | `0x4e554c4c`  | Cat's Eye Technologies | Funge-98 Null Fingerprint               |
|      ❌      |    ✅     | ORTH | `0x4f525448`  | Cat's Eye Technologies | Orthogonal Easement Library             |
|      ❌      |    ✅     | PERL | `0x5045524c`  | Cat's Eye Technologies | Generic Interface to the Perl Language  |
|      ❌      |    ✅     | REFC | `0x52454643`  | Cat's Eye Technologies | Referenced Cells Extension              |
|      ✅      |    ✅     | ROMA | `0x524f4d41`  | Cat's Eye Technologies | Funge-98 Roman Numerals                 |
|      ❌      |    ✅     | TOYS | `0x544f5953`  | Cat's Eye Technologies | Funge-98 Standard Toys                  |
|      ❌      |    ✅     | TURT | `0x54555254`  | Cat's Eye Technologies | Simple Turtle Graphics Library          |
|      ❌      |    ✅     | 3DSP | `0x33445350`  |          RCS           | 3D space manipulation extension         |
|      ❌      |    ❌     | ARRY | `0x41525259`  |          RCS           | Arrays                                  |
|      ❌      |    ✅     | BASE | `0x42415345`  |          RCS           | I/O for numbers in other bases          |
|      ❌      |    ❌     | BOOL | `0x424F4F4C`  |          RCS           | Logic functions                         |
|      ❌      |    ❌     | COPT | `0x434f5054`  |          RCS           | Command line arguments                  |
|      ❌      |    ✅     | CPLI | `0x43504C49`  |          RCS           | Complex Integer extension               |
|      ❌      |    ✅     | DATE | `0x44415445`  |          RCS           | Date Functions                          |
|      ❌      |    ✅     | DIRF | `0x44495246`  |          RCS           | Directory functions extension           |
|      ❌      |    ❌     | EMEM | `0x454d454d`  |          RCS           | Extended memory                         |
|      ❌      |    ✅     | EVAR | `0x45564152`  |          RCS           | Environment variables extension         |
|      ❌      |    ❌     | EXEC | `0x45584543`  |          RCS           | Various types of k-like execs           |
|      ✅      |    ✅     | FILE | `0x46494C45`  |          RCS           | File I/O functions                      |
|      ❌      |    ✅     | FING | `0x46494e47`  |          RCS           | Operate on single fingerprint semantics |
|      ❌      |    ❌     | FNGR | `0x464E4752`  |          RCS           | Fingerprint management extension        |
|      ❌      |    ❌     | FOBJ | `0x464f424a`  |          RCS           | Object Oriented extension               |
|      ❌      |    ❌     | FORK | `0x464F524B`  |          RCS           | Fork Process                            |
|      ❌      |    ✅     | FPDP | `0x46504450`  |          RCS           | Double precision floating point         |
|      ❌      |    ❌     | FPRT | `0x46505254`  |          RCS           | Formatted print                         |
|      ❌      |    ✅     | FPSP | `0x46505350`  |          RCS           | Single precision floating point         |
|      ❌      |    ✅     | FIXP | `0x46495850`  |          RCS           | Some useful fixed point math functions  |
|      ❌      |    ✅     | FRTH | `0x46525448`  |          RCS           | Some common forth commands              |
|      ❌      |    ❌     | ICAL | `0x4943414c`  |          RCS           | Some Intercal-like functions            |
|      ❌      |    ✅     | IIPC | `0x49495043`  |          RCS           | Inter IP communicaiton extension        |
|      ❌      |    ✅     | IMAP | `0x494D4150`  |          RCS           | Instruction remap extension             |
|      ❌      |    ❌     | IMTH | `0x494d5448`  |          RCS           | Some integer math functions             |
|      ❌      |    ✅     | INDV | `0x494E4456`  |          RCS           | Pointer functions                       |
|      ❌      |    ❌     | IPMD | `0x49504d44`  |          RCS           | IP dimension modes                      |
|      ❌      |    ❌     | LONG | `0x4c4f4e47`  |          RCS           | Long Integers                           |
|      ❌      |    ❌     | MACR | `0x4d414352`  |          RCS           | Macro Extension                         |
|      ❌      |    ❌     | MSGQ | `0x44d534751` |          RCS           | SysV IPC Message Queues                 |
|      ❌      |    ❌     | MVRS | `0x4d565253`  |          RCS           | Multiverse extension                    |
|      ❌      |    ❌     | RAND | `0x52414e44`  |          RCS           | Random Numbers                          |
|      ❌      |    ✅     | REXP | `0x52455850`  |          RCS           | Regular Expression Matching             |
|      ❌      |    ❌     | SETS | `0x53455453`  |          RCS           | Set operations                          |
|      ❌      |    ❌     | SGNE | `0x53474e45`  |          RCS           | Extension to SGNL                       |
|      ❌      |    ❌     | SMEM | `0x534d454d`  |          RCS           | SysV IPC Shared Memory                  |
|      ❌      |    ❌     | SMPH | `0x534d5048`  |          RCS           | SysV IPC Semaphores                     |
|      ❌      |    ✅     | SOCK | `0x534F434B`  |          RCS           | tcp/ip socket extension                 |
|      ❌      |    ❌     | SORT | `0x534f5254`  |          RCS           | Sorting Functions                       |
|      ❌      |    ❌     | STCK | `0x5354434b`  |          RCS           | Stack Manipulation                      |
|      ❌      |    ✅     | STRN | `0x5354524E`  |          RCS           | String functions                        |
|      ❌      |    ✅     | SUBR | `0x53554252`  |          RCS           | Subroutine extension                    |
|      ❌      |    ✅     | TIME | `0x54494D45`  |          RCS           | Time and Date functions                 |
|      ❌      |    ✅     | TERM | `0x5445524D`  |          RCS           | Terminal extension                      |
|      ❌      |    ✅     | TRDS | `0x54524453`  |          RCS           | IP travel in time and space             |
|      ❌      |    ❌     | TRGR | `0x54524752`  |          RCS           | Triggers                                |
|      ❌      |    ❌     | UNIX | `0x554e4958`  |          RCS           | Some Unix access functions              |
|      ❌      |    ❌     | WIND | `0x57494E44`  |          RCS           | Windows extensions                      |
|      ❌      |    ✅     | JSTR | `0x4a535452`  |     Jesse Van Herk     | 3d P and G for 0gnirts                  |
|      ❌      |    ❌     | SGNL | `0x53474E4C`  |     Jesse Van Herk     | Signal handling                         |
|      ❌      |    ✅     | NCRS | `0x4e435253`  |     Jesse Van Herk     | Ncurses Routines                        |
|      ❌      |    ✅     | SCKE | `0x53434b45`  |       GLFunge98        | Extensions to SOCK                      |
|      ❌      |    ❌     | CFFI | `0x43464649`  |        oshaboy         | C Foreign Function Interface            |
|      ❌      |    ❌     | IFFI | `0x49464649`  |        catb.org        | C-INTERCAL Foreign Function Interface   |
