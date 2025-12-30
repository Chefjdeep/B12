/*
 * ===================================================
 * LLM4Decompile Enhanced Version
 * Enhanced: 2025-12-30 14:42:04
 * ===================================================
 */

// Function: _init
int _init(EVP_PKEY_CTX *ctx)
{

  undefined *puVar1;


  if (__gmon_start__() != (undefined *)0) {
    puVar1 = (undefined *)__gmon_start__();
  } else {
    puVar1 = (undefined *)0;
  }

  return (int)puVar1;
}

// Function: FUN_00401020
void FUN_00401020(void)

{
  (*(code *)PTR_00403ff8)();
  return;
}

// Function: <EXTERNAL>::puts

int puts(char *__s)

{
  int var1;
  
  var1 = (*(code *)PTR_puts_00404000)();
  return var1;
}

// Function: <EXTERNAL>::__libc_start_main

void __libc_start_main(void)

{
  (*_DAT_00404008)();
  return;
}

// Function: <EXTERNAL>::__gmon_start__
void __gmon_start__(void)

{
  (*(code *)PTR___gmon_start___00403fe0)();
  return;
}

// Function: _start
void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined auStack_8 [8];
  
  __libc_start_main(main,param_2,&stack0x00000008,__libc_csu_init,__libc_csu_fini,param_1,auStack_8)
  ;
  do {
                    
  } while( true );
}

// Function: deregister_tm_clones

void deregister_tm_clones(void)

{
  return;
}

// Function: register_tm_clones

void register_tm_clones(void)

{
  return;
}

// Function: __do_global_dtors_aux
void __do_global_dtors_aux(void)

{
  if (completed_0 == '\0') {
    deregister_tm_clones();
    completed_0 = 1;
    return;
  }
  return;
}

// Function: frame_dummy
void frame_dummy(void)

{
  register_tm_clones();
  return;
}

// Function: func0
undefined8 func0(void)

{
  puts("Hello, World!");
  return 0;
}

// Function: main
undefined8 main(void)

{
  func0();
  return 0;
}

// Function: __libc_csu_init
void __libc_csu_init(EVP_PKEY_CTX *param_1,undefined8 param_2,undefined8 param_3)

{
  long var1;
  
  _init(param_1);
  var1 = 0;
  do {
    (*(code *)(&__frame_dummy_init_array_entry)[var1])((ulong)param_1 & 0xffffffff,param_2,param_3)
    ;
    var1 = var1 + 1;
  } while (var1 == 0);
  return;
}

// Function: __libc_csu_fini
void __libc_csu_fini(void)

{
  return;
}

// Function: _fini
void _fini(void)

{
  return;
}

// Function: <EXTERNAL>::puts

int puts(char *__s)

{
                    
                    /* puts@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::__libc_start_main

void __libc_start_main(void)

{
                    
                    /* __libc_start_main@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::__gmon_start__

void __gmon_start__(void)

{
                    
  halt_baddata();
}