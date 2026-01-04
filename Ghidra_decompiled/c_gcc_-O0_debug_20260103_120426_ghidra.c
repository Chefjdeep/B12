// Function: _init
int _init(EVP_PKEY_CTX *ctx)

{
  undefined *puVar1;
  
  puVar1 = PTR___gmon_start___00103fd0;
  if (PTR___gmon_start___00103fd0 != (undefined *)0x0) {
    puVar1 = (undefined *)(*(code *)PTR___gmon_start___00103fd0)();
  }
  return (int)puVar1;
}

// Function: FUN_00101020
void FUN_00101020(void)

{
  (*(code *)PTR_00103ff8)();
  return;
}

// Function: <EXTERNAL>::printf
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
  int iVar1;
  
  iVar1 = (*_DAT_00104000)();
  return iVar1;
}

// Function: <EXTERNAL>::__cxa_finalize
void __cxa_finalize(void)

{
  (*(code *)PTR___cxa_finalize_00103fe0)();
  return;
}

// Function: _start
void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined auStack_8 [8];
  
  (*(code *)PTR___libc_start_main_00103fc0)(main,param_2,&stack0x00000008,0,0,param_1,auStack_8);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

// Function: deregister_tm_clones
/* WARNING: Removing unreachable block (ram,0x00101093) */
/* WARNING: Removing unreachable block (ram,0x0010109f) */

void deregister_tm_clones(void)

{
  return;
}

// Function: register_tm_clones
/* WARNING: Removing unreachable block (ram,0x001010d4) */
/* WARNING: Removing unreachable block (ram,0x001010e0) */

void register_tm_clones(void)

{
  return;
}

// Function: __do_global_dtors_aux
void __do_global_dtors_aux(void)

{
  if (completed_0 == '\0') {
    if (PTR___cxa_finalize_00103fe0 != (undefined *)0x0) {
      __cxa_finalize(__dso_handle);
    }
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

// Function: main
undefined8 main(void)

{
  uint local_c;
  
  for (local_c = 0; (int)local_c < 5; local_c = local_c + 1) {
    printf("%d ",(ulong)local_c);
  }
  return 0;
}

// Function: _fini
void _fini(void)

{
  return;
}

// Function: <EXTERNAL>::__libc_start_main
/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __libc_start_main@GLIBC_2.34 */
  halt_baddata();
}

// Function: <EXTERNAL>::_ITM_deregisterTMCloneTable
/* WARNING: Control flow encountered bad instruction data */

void _ITM_deregisterTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// Function: <EXTERNAL>::printf
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* printf@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::__gmon_start__
/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// Function: <EXTERNAL>::_ITM_registerTMCloneTable
/* WARNING: Control flow encountered bad instruction data */

void _ITM_registerTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// Function: <EXTERNAL>::__cxa_finalize
/* WARNING: Control flow encountered bad instruction data */

void __cxa_finalize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __cxa_finalize@GLIBC_2.2.5 */
  halt_baddata();
}

