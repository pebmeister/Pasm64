pasm64.exe -dir ../include/ bootload.asm -c64 -l loader.lst -o loader.prg -s loader.sym -v
pasm64.exe -dir ../include/ macros.asm pagezero.asm kernal.asm basic.asm install.asm wedge.asm vars.asm main.asm init.asm pass1.asm pass2.asm getlinenum.asm findlinenum.asm insertlinenum.asm movelines.asm util.asm debug.asm storage.asm -c64 -l renum.lst -o renum.prg -s renum.sym -v
