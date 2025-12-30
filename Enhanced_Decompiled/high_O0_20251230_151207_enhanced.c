// Function: _init
int _init(EVP_PKEY_CTX *ctx)

{
  undefined *puVar1;
  
  puVar1 = PTR___gmon_start___00403fe0;
  if (PTR___gmon_start___00403fe0 != (undefined *)0x0) {
    puVar1 = (undefined *)__gmon_start__();
  }
  return (int)puVar1;
}

// Function: FUN_00401020
void FUN_00401020(void)

{
  (*(code *)PTR_00403ff8)();
  return;
}

// Function: <EXTERNAL>::free
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *__ptr)

{
  (*(code *)PTR_free_00404000)();
  return;
}

// Function: <EXTERNAL>::puts
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_puts_00404008)();
  return iVar1;
}

// Function: <EXTERNAL>::printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_printf_00404010)();
  return iVar1;
}

// Function: <EXTERNAL>::memset
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memset(void *__s,int __c,size_t __n)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_memset_00404018)();
  return pvVar1;
}

// Function: <EXTERNAL>::__libc_start_main
void __libc_start_main(void)

{
  (*(code *)PTR___libc_start_main_00404020)();
  return;
}

// Function: <EXTERNAL>::malloc
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * malloc(size_t __size)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_malloc_00404028)();
  return pvVar1;
}

// Function: <EXTERNAL>::fwrite
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
  size_t sVar1;
  
  sVar1 = (*_DAT_00404030)();
  return sVar1;
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
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

// Function: deregister_tm_clones
/* WARNING: Removing unreachable block (ram,0x004010e7) */
/* WARNING: Removing unreachable block (ram,0x004010f1) */

void deregister_tm_clones(void)

{
  return;
}

// Function: register_tm_clones
/* WARNING: Removing unreachable block (ram,0x00401128) */

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
  undefined8 uVar1;
  undefined8 local_38;
  undefined8 local_30;
  undefined local_28;
  void *local_20;
  ulong local_18;
  long local_10;
  
  puts("Starting suspicious memory operations...");
  local_38 = 0x48c0314890909090;
  local_30 = 0xd23148f63148ff31;
  local_28 = 0xc3;
  printf("Simulated payload size: %zu bytes\n",0x11);
  local_20 = malloc(0x100);
  if (local_20 == (void *)0x0) {
    fwrite("malloc failed\n",1,0xe,stderr);
    uVar1 = 1;
  }
  else {
    memset(local_20,0x90,0x100);
    local_10 = 0;
    for (local_18 = 0; local_18 < 0x11; local_18 = local_18 + 1) {
      local_10 = local_10 + (ulong)*(byte *)((long)&local_38 + local_18);
    }
    printf("Simulated payload checksum: %lu\n",local_10);
    free(local_20);
    puts("Exiting suspicious routine.");
    uVar1 = 0;
  }
  return uVar1;
}

// Function: main
void main(void)

{
  func0();
  return;
}

// Function: __libc_csu_init
void __libc_csu_init(EVP_PKEY_CTX *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  
  _init(param_1);
  lVar1 = 0;
  do {
    (*(code *)(&__frame_dummy_init_array_entry)[lVar1])((ulong)param_1 & 0xffffffff,param_2,param_3)
    ;
    lVar1 = lVar1 + 1;
  } while (lVar1 == 0);
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

// Function: <EXTERNAL>::free
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *__ptr)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* free@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::puts
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* puts@GLIBC_2.2.5 */
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

// Function: <EXTERNAL>::memset
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memset(void *__s,int __c,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* memset@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::__libc_start_main
/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __libc_start_main@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::__gmon_start__
/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// Function: <EXTERNAL>::malloc
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * malloc(size_t __size)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* malloc@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::fwrite
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* fwrite@GLIBC_2.2.5 */
  halt_baddata();
}


============================================================
/* LLM4Decompile ENHANCED FUNCTION */

/* LLM4Decompile enhanced function - 2025-12-30 15:12:46 */
int func0(void)
{
  int uVar1;
  int local_38;
  int local_30;
  void local_28;
  void*local_20;
  ulong local_18;
  long local_10;

  puts("Starting suspicious memory operations...");
  local_38 = 0x48c0314890909090;
  local_30 = 0xd23148f63148ff31;
  local_28 = 0xc3;
  printf("Simulated payload size: %zu bytes\n", 0x11);
  local_20 = malloc(0x100);
  if (local_20 == (void*)0x0) {
    fwrite("malloc failed\n", 1, 0xe, stderr);
    uVar1 = 1;
  }
  else {
    memset(local_20, 0x90, 0x100);
    local_10 = 0;
    for (local_18 = 0; local_18 < 0x11; local_18 = local_18 + 1) {
      local_10 = local_18 + (ulong)*(byte*)((long)&local_38 + local_18);
    }
    printf("Simulated payload checksum: %lu\n", local_10);
    free(local_20);
    puts("Exiting suspicious routine.");
    uVar1 = 0;
  }
  return uVar1;
}