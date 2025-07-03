#ifndef AMANITA_FILE_HPP
#define AMANITA_FILE_HPP

/* C	(h --)	            Close a file
 * D	(0gnirts -- )	    Delete specified file
 * G	(h -- h 0gnirts b)	Read string from file (like c fgets)
 * L	(h -- h n)	        Get location of file pointer
 * O	(Va m 0gnirts -- h)	Open a file (Va=i/o buffer)
 *                          m	function
 *                          0	read
 *                          1	write
 *                          2	append
 *                          3	read/write
 *                          4	truncate read/write
 *                          5	append read/write
 * P	(h 0gnirts -- h)	Write string to file (like c fputs)
 * R	(h n -- h)	        Read n bytes from file to buffer
 * S	(h m n -- h)	    Seek to position n in file
 *                          m	function
 *                          0	from beginning
 *                          1	from current location
 *                          2	from end
 * W	(h n -- h)	        Write n bytes from buffer to file
 *
 * All file functions on failure act as r.
 * Functions W and R write cells as bytes, any cells containing values greater than 255 will have the top bits stripped.
 */

#include "common.hpp"

InstructionAction file_close(Fungespace &, InstructionPointer &ip);
InstructionAction file_delete(Fungespace &, InstructionPointer &ip);
InstructionAction file_read_string(Fungespace &, InstructionPointer &ip);
InstructionAction file_location(Fungespace &, InstructionPointer &ip);
InstructionAction file_open(Fungespace &, InstructionPointer &ip);
InstructionAction file_write_string(Fungespace &, InstructionPointer &ip);
InstructionAction file_read_bytes(Fungespace &, InstructionPointer &ip);
InstructionAction file_seek(Fungespace &, InstructionPointer &ip);
InstructionAction file_write_bytes(Fungespace &, InstructionPointer &ip);

const Fingerprint FNG_FILE{
        .id = 0x46494C45,
        .fns = {
                {Instruction::C, file_close},
                {Instruction::D, file_delete},
                {Instruction::G, file_read_string},
                {Instruction::L, file_location},
                {Instruction::O, file_open},
                {Instruction::P, file_write_string},
                {Instruction::R, file_read_bytes},
                {Instruction::S, file_seek},
                {Instruction::W, file_write_bytes},
        }};

#endif // AMANITA_FILE_HPP
