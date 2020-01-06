/*
Copyright (c) 2013, The Regents of the University of California (Regents).
All Rights Reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the name of the Regents nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


modified for shakti

*/

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

/*----------------------------------------------------------------------*/
/* Sections                                                             */
/*----------------------------------------------------------------------*/

SECTIONS
{

  /* text: test code section */
  . = 0x80000000;
  .text.init : { *(.text.init) }

  .tohost ALIGN(0x1000) : { *(.tohost) }

  .text : { *(.text) }

  .rodata : {
       __rodata_start = .;
       *(.rodata)
       *(.rodata.*)
       *(.gnu.linkonce.r.*)
       __rodata_end = .;
	} 

  .sdata : {
    __global_pointer$ = . + 0x800;
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
  }

  /* bss segment */
  .sbss : {
	   __sbss_start = .;
	   *(.sbss)
	   *(.sbss.*)
	   *(.gnu.linkonce.sb.*)
	   __sbss_end = .;
	}

  
	
/* data segment */
  .data : {
	   . = ALIGN(4);
	   __data_start = .;
	   *(.data)
	   *(.data.*)
	   *(.gnu.linkonce.d.*)
	   __data_end = .;
	}


  .bss : {
       . = ALIGN(4);
       __bss_start = .;
       *(.bss)
       *(.bss.*)
       *(.gnu.linkonce.b.*)
       *(COMMON)
       . = ALIGN(4);
       __bss_end = .;
    }


  /* thread-local data segment */
  .tdata :
  {
    _tls_data = .;
    *(.tdata.begin)
    *(.tdata)
    *(.tdata.end)
    _tls_end = .;
  }
  .tbss :
  {
    *(.tbss)
    *(.tbss.end)
  }

  .=ALIGN(4);
  _end = .;
  . = 0x8000fffc;
   /* 0x8000fffc is for 128kB memory. If you change memory size set it to size-4Bytes. for example if its 100000 set it to ffffc */
  _free_space = . - _end;
  _STACK_SIZE = _free_space / 2;
  _HEAP_SIZE = _STACK_SIZE;
   
    .stack : {
       _stack_end = .;
       _stack = .  - _STACK_SIZE;
    }
   . = _stack;
   .heap : {
       _heap = . - _HEAP_SIZE;
       _heap_end = .;
    }


  /* End of uninitalized data segement */


  
}


