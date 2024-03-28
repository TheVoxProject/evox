# Super simple Python script to make a single-file version of Evox. This needs seriously improved at some point, the current implementation is a massive hack, but it does work.

from pathlib import Path

cpp_file_path = Path("../evox.cpp")
hpp_file_path = Path("../evox.hpp")
output_file_path = Path("../single_file/evox_single.hpp")
if not output_file_path.parent.exists():
    output_file_path.parent.mkdir(parents=True)
cpp_file_contents = cpp_file_path.read_text()
hpp_file_contents = hpp_file_path.read_text()

cpp_file_contents = cpp_file_contents.replace('#include "evox.hpp"', '')
combined_contents = hpp_file_contents + '\n' + cpp_file_contents
output_file_path.write_text(combined_contents)
print("Single file created at: " + str(output_file_path))
