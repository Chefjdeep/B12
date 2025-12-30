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

// Function: <EXTERNAL>::system
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int system(char *__command)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_system_00404000)();
  return iVar1;
}

// Function: <EXTERNAL>::htons
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

uint16_t htons(uint16_t __hostshort)

{
  uint16_t uVar1;
  
  uVar1 = (*(code *)PTR_htons_00404008)();
  return uVar1;
}

// Function: <EXTERNAL>::printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_printf_00404010)();
  return iVar1;
}

// Function: <EXTERNAL>::__libc_start_main
void __libc_start_main(void)

{
  (*(code *)PTR___libc_start_main_00404018)();
  return;
}

// Function: <EXTERNAL>::inet_pton
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int inet_pton(int __af,char *__cp,void *__buf)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_inet_pton_00404020)();
  return iVar1;
}

// Function: <EXTERNAL>::connect
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int connect(int __fd,sockaddr *__addr,socklen_t __len)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_connect_00404028)();
  return iVar1;
}

// Function: <EXTERNAL>::socket
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int socket(int __domain,int __type,int __protocol)

{
  int iVar1;
  
  iVar1 = (*_DAT_00404030)();
  return iVar1;
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
  sockaddr local_38 [2];
  char *local_18;
  int local_c;
  
  local_c = socket(2,1,0);
  local_38[0].sa_family = 2;
  local_38[0].sa_data._0_2_ = htons(0x115c);
  inet_pton(2,"192.168.1.100",local_38[0].sa_data + 2);
  connect(local_c,local_38,0x10);
  system("echo Hello > test.txt");
  local_18 = "U29tZSBzZWNyZXQgdGV4dCBmb3IgdGVzdGluZw==";
  printf("Decoded string: %s\n","U29tZSBzZWNyZXQgdGV4dCBmb3IgdGVzdGluZw==");
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

// Function: <EXTERNAL>::system
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int system(char *__command)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* system@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::htons
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

uint16_t htons(uint16_t __hostshort)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* htons@GLIBC_2.2.5 */
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

// Function: <EXTERNAL>::inet_pton
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int inet_pton(int __af,char *__cp,void *__buf)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* inet_pton@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::connect
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int connect(int __fd,sockaddr *__addr,socklen_t __len)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* connect@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::socket
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int socket(int __domain,int __type,int __protocol)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* socket@GLIBC_2.2.5 */
  halt_baddata();
}


============================================================
/* LLM4Decompile ENHANCED FUNCTION */

/* LLM4Decompile enhanced function - 2025-12-30 15:24:52 */
int func0(void)
{
 int local_1c;
 char *local_18;

 local_1c = socket(2, 1, 0);

 local_18 = "U29tZSBzZWNyZXQgdGV4dCBmb3IgdGVzdGluZw==";

 {
  sockaddr local_38 [2];
  int local_c;

  local_c = socket(2, 1, 0);
  local_38[0].sa_family = 2;
  local_38[0].sa_data._0_2_ = htons(0x115c);
  inet_pton(2, "192.168.1.100", local_38[0].sa_data + 2);
  connect(local_c, local_38, 0x10);
 }

 system("echo Hello > test.txt");

 return 0;
}