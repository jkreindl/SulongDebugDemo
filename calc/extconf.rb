require 'mkmf'
extension_name = 'CalcExt'
dir_config(extension_name)
$CPPFLAGS = '-std=c++11'
create_makefile(extension_name)
