// Function: FUN_004011b0
void FUN_004011b0(void)

{
  code *pcVar1;
  int *piVar2;
  undefined4 *puVar3;
  UINT uExitCode;
  
  if (___dyn_tls_init_callback != (undefined *)0x0) {
    (*(code *)___dyn_tls_init_callback)(0,2,0);
  }
  _SetUnhandledExceptionFilter_4((LPTOP_LEVEL_EXCEPTION_FILTER)&LAB_00401000);
  ___cpu_features_init();
  _fesetenv(__CRT_fenv);
  __setargv();
  pcVar1 = _iob_exref;
  if (__CRT_fmode != 0) {
    __fmode = __CRT_fmode;
    __setmode(*(int *)(_iob_exref + 0x10),__CRT_fmode);
    __setmode(*(int *)(pcVar1 + 0x30),__CRT_fmode);
    __setmode(*(int *)(pcVar1 + 0x50),__CRT_fmode);
  }
  piVar2 = (int *)___p__fmode();
  *piVar2 = __fmode;
  __pei386_runtime_relocator();
  ___main();
  puVar3 = (undefined4 *)___p__environ();
  uExitCode = _main(__argc,DAT_00407000,(char **)*puVar3);
  __cexit();
                    /* WARNING: Subroutine does not return */
  _ExitProcess_4(uExitCode);
}

// Function: __mingw32_init_mainargs
void __mingw32_init_mainargs(void)

{
  char **local_14;
  _startupinfo local_10 [4];
  
  local_10[0].newmode = 0;
  ___getmainargs(&__argc,(char ***)&DAT_00407000,&local_14,__CRT_glob & 1,local_10);
  return;
}

// Function: _mainCRTStartup
void _mainCRTStartup(void)

{
  _func_4879 *in_stack_ffffffcc;
  
  __set_app_type(1);
  FUN_004011b0();
  __set_app_type(2);
  FUN_004011b0();
                    /* WARNING: Could not recover jumptable at 0x00401320. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  atexit(in_stack_ffffffcc);
  return;
}

// Function: _atexit
int __cdecl _atexit(_func_4879 *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00401320. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = atexit(param_1);
  return iVar1;
}

// Function: _func0
void _func0(void)

{
  _puts("func0 called from C");
  return;
}

// Function: _main
int __cdecl _main(int _Argc,char **_Argv,char **_Env)

{
  ___main();
  _func0();
  return 0;
}

// Function: __setargv
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl __setargv(void)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  char *pcVar11;
  uint uStackY_60;
  LPSTR pCVar12;
  char acStack_4c [8];
  int local_44;
  undefined *local_40;
  uint local_3c;
  char *local_38;
  int local_34;
  uint local_30;
  undefined local_2c [4];
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  
  if ((__CRT_glob & 2) == 0) {
    uStackY_60 = 0x401795;
    iVar8 = __mingw32_init_mainargs();
    return iVar8;
  }
  uStackY_60 = 0x4014ab;
  pcVar3 = _GetCommandLineA_0();
  uStackY_60 = 0x4014b8;
  pCVar12 = pcVar3;
  local_40 = &stack0xffffffa4;
  _strlen(pcVar3);
  uStackY_60 = 0x4014c7;
  uVar4 = ___chkstk_ms((char)pCVar12);
  iVar8 = -uVar4;
  local_20 = 0;
  local_30 = 0;
  local_34 = 0;
  local_38 = acStack_4c + iVar8;
  local_3c = __CRT_glob & 0x4400 | 0x10;
  uVar4 = 0;
  pcVar6 = acStack_4c + iVar8;
LAB_00401500:
  do {
    cVar1 = *pcVar3;
joined_r0x0040150b:
    iVar10 = (int)cVar1;
    if (iVar10 == 0) {
      if (uVar4 != 0) {
        pcVar5 = pcVar6 + uVar4;
        pcVar3 = pcVar6;
        do {
          pcVar9 = pcVar3 + 1;
          *pcVar3 = '\\';
          pcVar6 = pcVar5;
          pcVar3 = pcVar9;
        } while (pcVar9 != pcVar5);
      }
      if ((local_38 < pcVar6) || (local_34 != 0)) {
        *pcVar6 = '\0';
        *(undefined4 *)(&stack0xffffffac + iVar8) = 0;
        *(undefined **)(&stack0xffffffb0 + iVar8) = local_2c;
        *(uint *)(&stack0xffffffa8 + iVar8) = local_3c;
        *(char **)(&stack0xffffffa4 + iVar8) = local_38;
        *(undefined4 *)((int)&uStackY_60 + iVar8) = 0x401786;
        ___mingw_glob(*(char **)(&stack0xffffffa4 + iVar8),*(uint *)(&stack0xffffffa8 + iVar8),
                      *(undefined **)(&stack0xffffffac + iVar8),
                      *(char ***)(&stack0xffffffb0 + iVar8));
      }
      __argc = local_28;
      DAT_00407000 = local_24;
      return local_24;
    }
    pcVar3 = pcVar3 + 1;
    if (cVar1 == '?') goto LAB_004016a3;
    if (cVar1 < '@') {
      iVar7 = (int)uVar4 >> 1;
      if (cVar1 != '\'') {
        if (cVar1 == '*') goto LAB_004016a3;
        if (cVar1 != '\"') goto LAB_00401640;
        if (iVar7 != 0) {
          pcVar9 = pcVar6 + iVar7;
          pcVar5 = pcVar6;
          do {
            pcVar11 = pcVar5 + 1;
            *pcVar5 = '\\';
            pcVar6 = pcVar9;
            pcVar5 = pcVar11;
          } while (pcVar11 != pcVar9);
        }
        if ((local_30 == 0x27) || ((uVar4 & 1) != 0)) break;
        local_30 = local_30 ^ 0x22;
        cVar1 = *pcVar3;
        uVar4 = 0;
        local_34 = 1;
        goto joined_r0x0040150b;
      }
      if ((__CRT_glob & 0x10) == 0) {
LAB_00401640:
        pcVar5 = pcVar6 + uVar4;
        pcVar9 = pcVar6;
        if (uVar4 != 0) {
          do {
            pcVar11 = pcVar6 + 1;
            *pcVar6 = '\\';
            pcVar6 = pcVar11;
            pcVar9 = pcVar5;
          } while (pcVar11 != pcVar5);
        }
        if (local_30 == 0) {
          if (*(int *)__mb_cur_max_exref == 1) {
            if ((*(byte *)(*(int *)_pctype_exref + iVar10 * 2) & 0x40) == 0) goto LAB_0040168e;
          }
          else {
            *(undefined4 *)(&stack0xffffffa8 + iVar8) = 0x40;
            *(int *)(&stack0xffffffa4 + iVar8) = iVar10;
            local_44 = iVar10;
            *(undefined4 *)((int)&uStackY_60 + iVar8) = 0x401683;
            iVar7 = __isctype(*(int *)(&stack0xffffffa4 + iVar8),*(int *)(&stack0xffffffa8 + iVar8))
            ;
            iVar10 = local_44;
            if (iVar7 == 0) {
LAB_0040168e:
              if (iVar10 != 9) goto LAB_00401697;
            }
          }
          if ((local_38 < pcVar9) || (local_34 != 0)) {
            *pcVar9 = '\0';
            *(undefined4 *)(&stack0xffffffac + iVar8) = 0;
            *(undefined **)(&stack0xffffffb0 + iVar8) = local_2c;
            uVar4 = local_3c;
            *(uint *)(&stack0xffffffa8 + iVar8) = local_3c;
            pcVar6 = local_38;
            *(char **)(&stack0xffffffa4 + iVar8) = local_38;
            *(undefined4 *)((int)&uStackY_60 + iVar8) = 0x4017e4;
            ___mingw_glob(*(char **)(&stack0xffffffa4 + iVar8),*(uint *)(&stack0xffffffa8 + iVar8),
                          *(undefined **)(&stack0xffffffac + iVar8),
                          *(char ***)(&stack0xffffffb0 + iVar8));
            local_34 = 0;
            local_3c = uVar4 | 1;
            uVar4 = 0;
          }
          else {
            uVar4 = 0;
            local_34 = 0;
            pcVar6 = pcVar9;
          }
        }
        else {
LAB_00401697:
          *pcVar9 = cVar1;
          uVar4 = 0;
          pcVar6 = pcVar9 + 1;
        }
      }
      else {
        if (iVar7 != 0) {
          pcVar9 = pcVar6 + iVar7;
          pcVar5 = pcVar6;
          do {
            pcVar11 = pcVar5 + 1;
            *pcVar5 = '\\';
            pcVar6 = pcVar9;
            pcVar5 = pcVar11;
          } while (pcVar11 != pcVar9);
        }
        if ((local_30 == 0x22) || ((uVar4 & 1) != 0)) {
          *pcVar6 = '\'';
          uVar4 = 0;
          local_34 = 1;
          pcVar6 = pcVar6 + 1;
        }
        else {
          local_30 = local_30 ^ 0x27;
          uVar4 = 0;
          local_34 = 1;
        }
      }
      goto LAB_00401500;
    }
    if (cVar1 == '\\') {
      if (local_30 == 0x27) {
        *pcVar6 = '\\';
        pcVar6 = pcVar6 + 1;
      }
      else {
        uVar4 = uVar4 + 1;
      }
      goto LAB_00401500;
    }
    if (cVar1 == '\x7f') {
LAB_004016a3:
      if (uVar4 == 0) {
        bVar2 = iVar10 == 0x7f || local_30 != 0;
        goto LAB_0040161b;
      }
      bVar2 = iVar10 == 0x7f || local_30 != 0;
    }
    else {
      if (cVar1 != '[') goto LAB_00401640;
      if ((__CRT_glob & 0x20) != 0) goto LAB_004016a3;
      bVar2 = true;
      pcVar5 = pcVar6;
      if (uVar4 == 0) goto LAB_00401632;
    }
    pcVar5 = pcVar6 + uVar4;
    pcVar9 = pcVar6;
    do {
      pcVar6 = pcVar9 + 1;
      *pcVar9 = '\\';
      pcVar9 = pcVar6;
    } while (pcVar6 != pcVar5);
LAB_0040161b:
    pcVar5 = pcVar6;
    if (bVar2) {
LAB_00401632:
      pcVar6 = pcVar5 + 1;
      *pcVar5 = '\x7f';
    }
    *pcVar6 = cVar1;
    uVar4 = 0;
    pcVar6 = pcVar6 + 1;
  } while( true );
  *pcVar6 = '\"';
  uVar4 = 0;
  local_34 = 1;
  pcVar6 = pcVar6 + 1;
  goto LAB_00401500;
}

// Function: ___cpu_features_init
/* WARNING: Removing unreachable block (ram,0x00401914) */
/* WARNING: Removing unreachable block (ram,0x00401906) */
/* WARNING: Removing unreachable block (ram,0x0040185e) */
/* WARNING: Removing unreachable block (ram,0x0040184f) */
/* WARNING: Removing unreachable block (ram,0x004018de) */
/* WARNING: Removing unreachable block (ram,0x004018e6) */
/* WARNING: Removing unreachable block (ram,0x004018e9) */
/* WARNING: Removing unreachable block (ram,0x004018f1) */
/* WARNING: Removing unreachable block (ram,0x004018f4) */
/* WARNING: Removing unreachable block (ram,0x004018f9) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ___cpu_features_init(void)

{
  int *piVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  byte in_VIP;
  byte in_ID;
  undefined auStack_210 [520];
  
  uVar4 = (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000;
  if (((((uint)(((uVar4 ^ 0x200000) & 0x200000) != 0) * 0x200000 ^ uVar4) & 0x200000) != 0) &&
     (piVar1 = (int *)cpuid_basic_info(0), *piVar1 != 0)) {
    iVar2 = cpuid_Version_info(1);
    uVar4 = *(uint *)(iVar2 + 8);
    ____cpu_features = (uint)((uVar4 & 0x100) != 0);
    if ((*(uint *)(iVar2 + 0xc) & 0x2000) != 0) {
      ____cpu_features = ____cpu_features | 0x80;
    }
    if ((uVar4 & 0x8000) != 0) {
      ____cpu_features = ____cpu_features | 2;
    }
    if ((uVar4 & 0x800000) != 0) {
      ____cpu_features = ____cpu_features | 4;
    }
    if ((uVar4 & 0x1000000) != 0) {
      ____cpu_features = ____cpu_features | 8;
      _fxsave(auStack_210);
      _fxrstor(auStack_210);
      _fxsave(auStack_210);
      LOCK();
      UNLOCK();
      _fxrstor(auStack_210);
    }
    puVar3 = (uint *)cpuid(0x80000000);
    if (0x80000000 < *puVar3) {
      iVar2 = cpuid(0x80000001);
      uVar4 = 0;
      if ((int)*(uint *)(iVar2 + 8) < 0) {
        uVar4 = 0x100;
      }
      if ((*(uint *)(iVar2 + 8) & 0x40000000) != 0) {
        uVar4 = uVar4 | 0x200;
      }
      ____cpu_features = ____cpu_features | uVar4;
    }
  }
  return;
}

// Function: ___do_global_ctors
void ___do_global_ctors(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = ___CTOR_LIST__;
  if (___CTOR_LIST__ == -1) {
    iVar1 = 0;
    do {
      iVar2 = iVar1;
      iVar1 = iVar2 + 1;
    } while ((&___CTOR_LIST__)[iVar2 + 1] != 0);
  }
  for (; iVar2 != 0; iVar2 = iVar2 + -1) {
    (*(code *)(&___CTOR_LIST__)[iVar2])();
  }
  _atexit((_func_4879 *)&___do_global_dtors);
  return;
}

// Function: ___main
void ___main(void)

{
  if (_bss != 0) {
    return;
  }
  _bss = 1;
  ___do_global_ctors();
  return;
}

// Function: tls_callback_1
undefined4 tls_callback_1(undefined4 param_1,int param_2)

{
  if ((param_2 != 3) && (param_2 != 0)) {
    return 1;
  }
  ___mingw_TLScallback(param_1,param_2);
  return 1;
}

// Function: ___dyn_tls_init@12
/* WARNING: Removing unreachable block (ram,0x00401a73) */
/* WARNING: Removing unreachable block (ram,0x00401a75) */
/* WARNING: Removing unreachable block (ram,0x00401a7f) */
/* WARNING: Removing unreachable block (ram,0x00401a81) */
/* WARNING: Removing unreachable block (ram,0x00401a88) */

undefined4 ___dyn_tls_init_12(undefined4 param_1,int param_2)

{
  if (__CRT_MT != 2) {
    __CRT_MT = 2;
  }
  if ((param_2 != 2) && (param_2 == 1)) {
    ___mingw_TLScallback(param_1,1);
  }
  return 1;
}

// Function: .text
void _text(void)

{
  DWORD *pDVar1;
  LPVOID pvVar2;
  DWORD DVar3;
  
  _EnterCriticalSection_4((LPCRITICAL_SECTION)&DAT_00407044);
  for (pDVar1 = _bss; pDVar1 != (DWORD *)0x0; pDVar1 = (DWORD *)pDVar1[2]) {
    pvVar2 = _TlsGetValue_4(*pDVar1);
    DVar3 = _GetLastError_0();
    if ((DVar3 == 0) && (pvVar2 != (LPVOID)0x0)) {
      (*(code *)pDVar1[1])(pvVar2);
    }
  }
  _LeaveCriticalSection_4((LPCRITICAL_SECTION)&DAT_00407044);
  return;
}

// Function: ___mingw_TLScallback
undefined4 __cdecl ___mingw_TLScallback(undefined4 param_1,int param_2)

{
  if (param_2 != 1) {
    if (param_2 == 0) {
      if (DAT_00407040 != 0) {
        _text();
      }
      if (DAT_00407040 == 1) {
        DAT_00407040 = 0;
        _DeleteCriticalSection_4((LPCRITICAL_SECTION)&DAT_00407044);
      }
    }
    else if ((param_2 == 3) && (DAT_00407040 != 0)) {
      _text();
    }
    return 1;
  }
  if (DAT_00407040 == 0) {
    _InitializeCriticalSection_4((LPCRITICAL_SECTION)&DAT_00407044);
  }
  DAT_00407040 = 1;
  return 1;
}

// Function: .text
void _text(char *param_1)

{
  FILE *_File;
  
  _File = (FILE *)(_iob_exref + 0x40);
  _fwrite("Mingw runtime failure:\n",1,0x17,_File);
  _vfprintf(_File,param_1,&stack0x00000008);
                    /* WARNING: Subroutine does not return */
  _abort();
}

// Function: FUN_00401d50
void __fastcall FUN_00401d50(size_t param_1,void *param_2)

{
  LPCVOID in_EAX;
  SIZE_T SVar1;
  DWORD local_3c;
  _MEMORY_BASIC_INFORMATION local_38;
  
  SVar1 = _VirtualQuery_12(in_EAX,&local_38,0x1c);
  if (SVar1 == 0) {
                    /* WARNING: Subroutine does not return */
    _text("  VirtualQuery failed for %d bytes at address %p");
  }
  if ((local_38.Protect == 0x40) || (local_38.Protect == 4)) {
    _memcpy(in_EAX,param_2,param_1);
  }
  else {
    _VirtualProtect_16(local_38.BaseAddress,local_38.RegionSize,0x40,&local_3c);
    _memcpy(in_EAX,param_2,param_1);
    if ((local_38.Protect != 0x40) && (local_38.Protect != 4)) {
      _VirtualProtect_16(local_38.BaseAddress,local_38.RegionSize,local_3c,&local_3c);
      return;
    }
  }
  return;
}

// Function: __pei386_runtime_relocator
/* WARNING: Removing unreachable block (ram,0x00401e69) */
/* WARNING: Removing unreachable block (ram,0x00401f60) */
/* WARNING: Removing unreachable block (ram,0x00401e78) */
/* WARNING: Removing unreachable block (ram,0x00401e86) */
/* WARNING: Removing unreachable block (ram,0x00401e94) */
/* WARNING: Removing unreachable block (ram,0x00401f65) */
/* WARNING: Removing unreachable block (ram,0x00401f6b) */
/* WARNING: Removing unreachable block (ram,0x00401f76) */
/* WARNING: Removing unreachable block (ram,0x00401ea7) */
/* WARNING: Removing unreachable block (ram,0x00401eac) */
/* WARNING: Removing unreachable block (ram,0x00401ffb) */
/* WARNING: Removing unreachable block (ram,0x00401eb8) */
/* WARNING: Removing unreachable block (ram,0x00401ec7) */
/* WARNING: Removing unreachable block (ram,0x00401f80) */
/* WARNING: Removing unreachable block (ram,0x00401f8c) */
/* WARNING: Removing unreachable block (ram,0x00401f92) */
/* WARNING: Removing unreachable block (ram,0x00401eeb) */
/* WARNING: Removing unreachable block (ram,0x00401fe0) */
/* WARNING: Removing unreachable block (ram,0x00401ef4) */
/* WARNING: Removing unreachable block (ram,0x00401efd) */
/* WARNING: Removing unreachable block (ram,0x00401fb0) */
/* WARNING: Removing unreachable block (ram,0x00401fb9) */
/* WARNING: Removing unreachable block (ram,0x00401fbf) */
/* WARNING: Removing unreachable block (ram,0x00401f15) */
/* WARNING: Removing unreachable block (ram,0x00401f1a) */
/* WARNING: Removing unreachable block (ram,0x00401f22) */
/* WARNING: Removing unreachable block (ram,0x00401f50) */

void __pei386_runtime_relocator(void)

{
  if (_bss == 0) {
    _bss = 1;
  }
  return;
}

// Function: ___chkstk_ms
uint ___chkstk_ms(undefined1 param_1)

{
  uint in_EAX;
  uint uVar1;
  undefined4 *puVar2;
  uint uStack_8;
  
  puVar2 = (undefined4 *)&param_1;
  uVar1 = in_EAX;
  if (0xfff < in_EAX) {
    do {
      puVar2 = puVar2 + -0x400;
      *puVar2 = *puVar2;
      uVar1 = uVar1 - 0x1000;
    } while (0x1000 < uVar1);
  }
  uStack_8 = in_EAX;
  *(undefined4 *)((int)puVar2 - uVar1) = *(undefined4 *)((int)puVar2 - uVar1);
  return uStack_8;
}

// Function: _fesetenv
undefined4 __cdecl _fesetenv(int param_1)

{
  uint local_10;
  
  local_10 = 0x1f80;
  if (param_1 == -3) {
    _data = -1;
    goto LAB_00402071;
  }
  if (param_1 == -4) {
    _data = -2;
  }
  else {
    if (param_1 == 0) {
      param_1 = _data;
    }
    if (param_1 == -1) goto LAB_00402071;
    if (param_1 != -2) {
      local_10 = (uint)*(ushort *)(param_1 + 0x1c);
      goto LAB_00402071;
    }
  }
  _fpreset();
LAB_00402071:
  if ((___cpu_features & 0x10) != 0) {
    MXCSR = local_10;
  }
  return 0;
}

// Function: .text
undefined4 __fastcall _text(undefined4 param_1,uint param_2)

{
  char *pcVar1;
  char *in_EAX;
  uint uVar2;
  char cVar3;
  bool bVar4;
  
  if (in_EAX == (char *)0x0) {
    return 0;
  }
  uVar2 = 0;
  do {
    cVar3 = *in_EAX;
    if (cVar3 == '\0') {
      return 0;
    }
    while( true ) {
      if (((((byte)(param_2 >> 5) ^ 1) & 1) == 0) || (cVar3 != '\x7f')) {
        in_EAX = in_EAX + 1;
      }
      else {
        pcVar1 = in_EAX + 1;
        in_EAX = in_EAX + 2;
        if (*pcVar1 == '\0') {
          return 0;
        }
      }
      if (uVar2 != 0) break;
      if (cVar3 == '*') {
        return 1;
      }
      if (cVar3 == '?') {
        return 1;
      }
      bVar4 = cVar3 == '[';
      cVar3 = *in_EAX;
      uVar2 = (uint)bVar4;
      if (cVar3 == '\0') {
        return 0;
      }
    }
    if ((1 < (int)uVar2) && (cVar3 == ']')) {
      return 1;
    }
    uVar2 = uVar2 + (cVar3 != '!');
  } while( true );
}

// Function: FUN_00402150
undefined4 FUN_00402150(void)

{
  int in_EAX;
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (in_EAX == 0) {
    return 0;
  }
  iVar3 = *(int *)(in_EAX + 0xc) + 1;
  pvVar1 = _malloc(iVar3 * 4);
  *(void **)(in_EAX + 8) = pvVar1;
  uVar2 = 3;
  if (pvVar1 != (void *)0x0) {
    *(undefined4 *)(in_EAX + 4) = 0;
    if (0 < iVar3) {
      do {
        iVar3 = iVar3 + -1;
        *(undefined4 *)((int)pvVar1 + iVar3 * 4) = 0;
      } while (iVar3 != 0);
    }
    uVar2 = 0;
  }
  return uVar2;
}

// Function: FUN_004021c0
char * __fastcall FUN_004021c0(uint param_1,uint param_2)

{
  uint uVar1;
  char *in_EAX;
  int iVar2;
  int iVar3;
  char cVar4;
  uint _C;
  uint uVar5;
  char *pcVar6;
  
  _C = (uint)*in_EAX;
  if ((_C == 0x5d) || (uVar5 = _C, _C == 0x2d)) {
    if (_C == param_2) {
      pcVar6 = in_EAX + 1;
LAB_004023a0:
      do {
        cVar4 = *pcVar6;
        if (cVar4 == ']') goto LAB_004023d5;
        if (cVar4 == '\x7f') {
          if ((param_1 & 0x20) != 0) {
            pcVar6 = pcVar6 + 1;
            goto LAB_004023a0;
          }
          cVar4 = pcVar6[1];
          pcVar6 = pcVar6 + 1;
        }
        pcVar6 = pcVar6 + 1;
        if (cVar4 == '\0') {
          return (char *)0x0;
        }
      } while( true );
    }
    uVar5 = (uint)in_EAX[1];
    in_EAX = in_EAX + 1;
  }
  do {
    pcVar6 = in_EAX + 1;
    if (uVar5 == 0x5d) {
      return (char *)0x0;
    }
    if (uVar5 == 0x2d) {
      if (in_EAX[1] != ']') {
        uVar5 = (uint)in_EAX[1];
        if (uVar5 == 0) {
          return (char *)0x0;
        }
        pcVar6 = in_EAX + 2;
        if ((int)_C < (int)uVar5) {
          do {
            uVar1 = _C + 1;
            if ((param_1 & 0x4000) == 0) {
              iVar2 = _tolower(_C);
              iVar3 = _tolower(param_2);
              if (iVar2 == iVar3) {
LAB_00402317:
                goto LAB_00402322;
              }
            }
            else if (~param_2 + uVar1 == 0) goto LAB_00402317;
            _C = uVar1;
          } while (uVar5 != uVar1);
        }
        else if ((int)uVar5 < (int)_C) {
          do {
            uVar1 = _C - 1;
            if ((param_1 & 0x4000) == 0) {
              iVar2 = _tolower(_C);
              iVar3 = _tolower(param_2);
              if (iVar2 == iVar3) {
LAB_00402438:
                goto LAB_00402443;
              }
            }
            else if ((1 - param_2) + uVar1 == 0) goto LAB_00402438;
            _C = uVar1;
          } while (uVar5 != uVar1);
        }
        goto LAB_0040222b;
      }
      _C = 0x2d;
      cVar4 = ']';
    }
    else {
      if (uVar5 == 0) {
        return (char *)0x0;
      }
LAB_0040222b:
      if (uVar5 == 0x2f) {
        return (char *)0x0;
      }
      if (uVar5 == 0x5c) {
        return (char *)0x0;
      }
      cVar4 = *pcVar6;
      _C = uVar5;
    }
    if ((param_1 & 0x4000) == 0) {
      iVar2 = _tolower(_C);
      iVar3 = _tolower(param_2);
      if (iVar2 == iVar3) {
LAB_00402273:
        goto LAB_0040228e;
      }
    }
    else if (_C == param_2) goto LAB_00402273;
    uVar5 = (uint)cVar4;
    in_EAX = pcVar6;
  } while( true );
LAB_00402443:
  cVar4 = *pcVar6;
  if (cVar4 == ']') {
LAB_0040238a:
    return pcVar6 + 1;
  }
  if (cVar4 == '\x7f') {
    if ((param_1 & 0x20) != 0) {
      pcVar6 = pcVar6 + 1;
      goto LAB_00402443;
    }
    cVar4 = pcVar6[1];
    pcVar6 = pcVar6 + 1;
  }
  pcVar6 = pcVar6 + 1;
  if (cVar4 == '\0') {
    return (char *)0x0;
  }
  goto LAB_00402443;
LAB_00402322:
  cVar4 = *pcVar6;
  while( true ) {
    if (cVar4 == ']') goto LAB_0040238a;
    if (cVar4 != '\x7f') goto LAB_0040232d;
    if ((param_1 & 0x20) == 0) break;
    pcVar6 = pcVar6 + 1;
    cVar4 = *pcVar6;
  }
  cVar4 = pcVar6[1];
  pcVar6 = pcVar6 + 1;
LAB_0040232d:
  pcVar6 = pcVar6 + 1;
  if (cVar4 == '\0') {
    return (char *)0x0;
  }
  goto LAB_00402322;
LAB_0040228e:
  if (cVar4 == ']') {
LAB_004023d5:
    return pcVar6 + 1;
  }
  if (cVar4 == '\x7f') {
    if ((param_1 & 0x20) == 0) {
      cVar4 = pcVar6[1];
      pcVar6 = pcVar6 + 1;
      goto LAB_00402280;
    }
  }
  else {
LAB_00402280:
    if (cVar4 == '\0') {
      return (char *)0x0;
    }
  }
  pcVar6 = pcVar6 + 1;
  cVar4 = *pcVar6;
  goto LAB_0040228e;
}

// Function: FUN_00402480
int __fastcall FUN_00402480(uint param_1,char *param_2)

{
  char *in_EAX;
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  int _C;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  
  cVar3 = *in_EAX;
  if (((*param_2 != '.') || (cVar3 == '.')) || (iVar4 = cVar3 + -0x2e, (param_1 & 0x10000) != 0)) {
    pcVar8 = param_2 + 1;
    while( true ) {
      iVar4 = (int)cVar3;
      pcVar6 = in_EAX + 1;
      if (iVar4 == 0) break;
      if (cVar3 == '?') {
        if (pcVar8[-1] == '\0') {
          return 0x3f;
        }
      }
      else if (cVar3 == '[') {
        uVar5 = (uint)pcVar8[-1];
        if (uVar5 == 0) {
          return 0x5b;
        }
        if (in_EAX[1] == '!') {
          pcVar6 = in_EAX + 2;
          pcVar7 = FUN_004021c0(param_1,uVar5);
          if (pcVar7 == (char *)0x0) {
            cVar3 = in_EAX[2];
            if (cVar3 == ']') {
              pcVar6 = in_EAX + 3;
              cVar3 = in_EAX[3];
            }
            while (cVar3 != ']') {
              if (cVar3 == '\x7f') {
                if ((param_1 & 0x20) == 0) {
                  cVar3 = pcVar6[1];
                  pcVar6 = pcVar6 + 1;
                  goto LAB_00402640;
                }
              }
              else {
LAB_00402640:
                if (cVar3 == '\0') {
                  return 0x5d;
                }
              }
              pcVar6 = pcVar6 + 1;
              cVar3 = *pcVar6;
            }
            pcVar6 = pcVar6 + 1;
          }
        }
        else {
          pcVar6 = FUN_004021c0(param_1,uVar5);
        }
        if (pcVar6 == (char *)0x0) {
          return 0x5d;
        }
      }
      else {
        if (cVar3 == '*') {
          cVar3 = in_EAX[1];
          while (cVar3 == '*') {
            pcVar6 = pcVar6 + 1;
            cVar3 = *pcVar6;
          }
          if (cVar3 != '\0') {
            pcVar8 = pcVar8 + -1;
            do {
              iVar4 = FUN_00402480(param_1 | 0x10000,pcVar8);
              if (iVar4 == 0) {
                return 0;
              }
              cVar3 = *pcVar8;
              pcVar8 = pcVar8 + 1;
            } while (cVar3 != '\0');
            return iVar4;
          }
          return 0;
        }
        if ((((param_1 >> 5 ^ 1) & 1) == 0) || (iVar4 != 0x7f)) {
LAB_004024e2:
          pcVar7 = pcVar6;
        }
        else {
          iVar4 = (int)in_EAX[1];
          pcVar7 = in_EAX + 2;
          if (iVar4 == 0) goto LAB_004024e2;
        }
        _C = (int)pcVar8[-1];
        if (pcVar8[-1] == '\0') {
          _C = 0;
LAB_00402522:
          return iVar4 - _C;
        }
        if ((param_1 & 0x4000) == 0) {
          iVar1 = _tolower(iVar4);
          iVar2 = _tolower(_C);
          iVar1 = iVar1 - iVar2;
        }
        else {
          iVar1 = iVar4 - _C;
        }
        pcVar6 = pcVar7;
        if (iVar1 != 0) goto LAB_00402522;
      }
      cVar3 = *pcVar6;
      pcVar8 = pcVar8 + 1;
      in_EAX = pcVar6;
    }
    iVar4 = -(int)pcVar8[-1];
  }
  return iVar4;
}

// Function: FUN_004026a0
undefined4 __fastcall FUN_004026a0(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 in_EAX;
  void *pvVar4;
  
  pvVar4 = _realloc(*(void **)(param_2 + 8),
                    (*(int *)(param_2 + 0xc) + *(int *)(param_2 + 4)) * 4 + 8);
  if (pvVar4 != (void *)0x0) {
    iVar2 = *(int *)(param_2 + 4);
    iVar3 = *(int *)(param_2 + 0xc);
    *(void **)(param_2 + 8) = pvVar4;
    iVar1 = iVar2 + 1;
    *(int *)(param_2 + 4) = iVar1;
    *(undefined4 *)((int)pvVar4 + (iVar2 + iVar3) * 4) = in_EAX;
    *(undefined4 *)((int)pvVar4 + (iVar3 + iVar1) * 4) = 0;
    return 0;
  }
  return 1;
}

// Function: FUN_00402700
void __fastcall FUN_00402700(undefined4 param_1,int param_2)

{
  int *in_EAX;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  
  if (*in_EAX != 0) {
    FUN_00402700(param_1,param_2);
    param_1 = extraout_ECX;
  }
  if ((in_EAX[2] != 0) && (param_2 != 0)) {
    FUN_004026a0(param_1,param_2);
    param_1 = extraout_ECX_00;
  }
  if (in_EAX[1] != 0) {
    FUN_00402700(param_1,param_2);
  }
  _free(in_EAX);
  return;
}

// Function: FUN_00402750
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Removing unreachable block (ram,0x00402fb8) */
/* WARNING: Type propagation algorithm not settling */

uint __fastcall FUN_00402750(undefined *param_1,uint param_2,void *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  code *pcVar3;
  void **ppvVar4;
  char cVar5;
  char *in_EAX;
  uint uVar6;
  void *pvVar7;
  int iVar8;
  size_t sVar9;
  undefined4 *puVar10;
  int iVar11;
  char *pcVar12;
  undefined *puVar13;
  undefined4 *puVar14;
  char **ppcVar15;
  undefined4 extraout_ECX;
  void *extraout_ECX_00;
  void *extraout_ECX_01;
  void *extraout_ECX_02;
  void *extraout_ECX_03;
  void *extraout_ECX_04;
  void *extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  void *extraout_ECX_08;
  void *extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  int iVar16;
  char *pcVar17;
  undefined4 *puVar18;
  int *piVar19;
  int **ppiVar20;
  char *pcVar22;
  uint uVar23;
  char *pcVar24;
  int *piVar25;
  bool bVar26;
  char *pcStackY_80;
  size_t sStack_74;
  char acStack_70 [15];
  char local_61;
  char *local_60;
  undefined *local_5c;
  undefined *local_58;
  undefined *local_54;
  undefined4 *local_50;
  undefined4 *local_4c;
  int *local_48;
  undefined *local_44;
  code *local_40;
  char *local_3c;
  char *local_38;
  uint local_34;
  undefined4 local_30;
  undefined local_2c [8];
  int *local_24;
  undefined4 local_20;
  char **ppcVar21;
  
  local_40 = (code *)param_1;
  local_34 = param_2;
  if ((param_2 & 0x400) != 0) {
    pcStackY_80 = (char *)0x402acb;
    pcVar12 = in_EAX;
    local_44 = &stack0xffffff84;
    _strlen(in_EAX);
    pcStackY_80 = (char *)0x402ad9;
    uVar6 = ___chkstk_ms((char)pcVar12);
    iVar11 = -uVar6;
    pcVar12 = acStack_70 + iVar11;
    local_3c = pcVar12;
    cVar5 = *in_EAX;
    pcVar17 = in_EAX;
LAB_00402ae9:
    if (cVar5 == '\x7f') goto LAB_00402b15;
    while (pcVar22 = pcVar17, pcVar24 = pcVar12, cVar5 != '{') {
      while( true ) {
        pcVar12 = pcVar24 + 1;
        pcVar17 = pcVar22 + 1;
        *pcVar24 = cVar5;
        if ((cVar5 == '\0') || (cVar5 == '{')) {
          if (cVar5 != '{') goto LAB_0040276a;
          local_38 = pcVar12;
          goto LAB_00402b35;
        }
        cVar5 = pcVar22[1];
        if (cVar5 != '\x7f') break;
LAB_00402b15:
        cVar5 = pcVar17[1];
        *pcVar12 = '\x7f';
        if (cVar5 != '\0') {
          pcVar12[1] = cVar5;
          pcVar17 = pcVar17 + 2;
          cVar5 = *pcVar17;
          pcVar12 = pcVar12 + 2;
          goto LAB_00402ae9;
        }
        pcVar24 = pcVar12 + 1;
        pcVar22 = pcVar17 + 1;
        cVar5 = '\0';
      }
    }
    local_38 = pcVar12;
LAB_00402b35:
    iVar8 = 1;
    pcVar12 = local_38;
LAB_00402b3d:
    cVar5 = pcVar17[1];
    if (cVar5 == '\x7f') goto LAB_00402b6b;
    do {
      pcVar17 = pcVar17 + 1;
      pcVar22 = pcVar12;
      while( true ) {
        if ((cVar5 != '}') && ((cVar5 != ',' || (iVar8 != 1)))) {
          if (cVar5 == '{') {
            iVar8 = iVar8 + 1;
          }
          local_30 = (char *)CONCAT31(local_30._1_3_,cVar5 != '\0');
          pcVar12 = pcVar22 + 1;
          *pcVar22 = cVar5;
          if (cVar5 != '\0') goto LAB_00402b3d;
          pcVar22 = pcVar12;
          if (cVar5 == '\0') {
            return 1;
          }
          goto LAB_00402c90;
        }
        iVar8 = iVar8 + -1;
        if (iVar8 == 0) {
          pcVar12 = pcVar17;
          if (cVar5 != ',') goto LAB_00402c33;
          iVar8 = 1;
          pcVar24 = pcVar17;
          goto LAB_00402bf0;
        }
        *pcVar22 = cVar5;
        cVar5 = pcVar17[1];
        pcVar12 = pcVar22 + 1;
        if (cVar5 != '\x7f') break;
LAB_00402b6b:
        cVar5 = pcVar17[2];
        *pcVar12 = '\x7f';
        pcVar22 = pcVar12 + 2;
        pcVar12[1] = cVar5;
        if (cVar5 == '\0') {
          pcVar12[2] = '\0';
          return 1;
        }
        cVar5 = pcVar17[3];
        pcVar17 = pcVar17 + 3;
      }
    } while( true );
  }
LAB_0040276a:
  local_5c = &stack0xffffff84;
  pcStackY_80 = (char *)0x402775;
  pcVar12 = in_EAX;
  _strlen(in_EAX);
  pcStackY_80 = (char *)0x402786;
  uVar6 = ___chkstk_ms((char)pcVar12);
  iVar11 = -uVar6;
  ppiVar20 = (int **)(&stack0xffffff84 + iVar11);
  *(undefined4 *)((int)&sStack_74 + iVar11) = extraout_EDX;
  *(char **)(&stack0xffffff88 + iVar11) = in_EAX;
  *(char **)(&stack0xffffff84 + iVar11) = acStack_70 + iVar11;
  *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x40279c;
  pvVar7 = _memcpy(*(void **)(&stack0xffffff84 + iVar11),*(void **)(&stack0xffffff88 + iVar11),
                   *(size_t *)((int)&sStack_74 + iVar11));
  *(void **)(&stack0xffffff84 + iVar11) = pvVar7;
  *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x4027a4;
  local_30 = ___mingw_dirname(*(char **)(&stack0xffffff84 + iVar11));
  local_20 = 0;
  *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x4027b8;
  local_38 = (char *)FUN_00402150();
  uVar6 = local_34;
  if (local_38 != (char *)0x0) {
    return (uint)local_38;
  }
  *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x4027cf;
  iVar8 = _text(extraout_ECX,uVar6);
  if (iVar8 == 0) {
    *(char **)(&stack0xffffff84 + iVar11) = local_30;
    *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402cbb;
    _strlen(*(char **)(&stack0xffffff84 + iVar11));
    *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402cc9;
    uVar6 = ___chkstk_ms((&stack0xffffff84)[iVar11]);
    iVar8 = -uVar6;
    pcVar12 = acStack_70 + iVar8 + iVar11;
    pcVar17 = local_30;
    do {
      cVar5 = *pcVar17;
      if (cVar5 == '\x7f') {
        cVar5 = pcVar17[1];
        pcVar17 = pcVar17 + 1;
      }
      pcVar17 = pcVar17 + 1;
      *pcVar12 = cVar5;
      pcVar12 = pcVar12 + 1;
    } while (cVar5 != '\0');
    *(char **)(&stack0xffffff84 + iVar8 + iVar11) = acStack_70 + iVar8 + iVar11;
    *(undefined4 *)((int)&pcStackY_80 + iVar8 + iVar11) = 0x402d05;
    pcVar12 = _strdup(*(char **)(&stack0xffffff84 + iVar8 + iVar11));
    if (pcVar12 == (char *)0x0) {
      return 1;
    }
    *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402d17;
    local_38 = (char *)FUN_004026a0(extraout_ECX_06,(int)local_2c);
  }
  else {
    *(undefined **)(&stack0xffffff84 + iVar11) = local_2c;
    pcVar3 = local_40;
    *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x4027ec;
    local_38 = (char *)FUN_00402750(pcVar3,uVar6 | 0x8000,*(void **)(&stack0xffffff84 + iVar11));
  }
  uVar6 = local_34;
  if (local_38 != (char *)0x0) {
    return (uint)local_38;
  }
  if ((in_EAX[1] == '/') || (bVar26 = in_EAX[1] == '\\', bVar26)) {
LAB_0040281b:
    *(char **)(&stack0xffffff84 + iVar11) = local_30;
    *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402826;
    sVar9 = _strlen(*(char **)(&stack0xffffff84 + iVar11));
    local_3c = in_EAX + sVar9;
    if (in_EAX < local_3c) {
      local_61 = *local_3c;
      if ((local_61 == '/') || (local_61 == '\\')) {
      }
      else {
        do {
          pcVar12 = local_3c + -1;
          if (in_EAX == pcVar12) {
            local_61 = local_3c[-1];
            local_3c = pcVar12;
            goto LAB_00402879;
          }
          local_61 = local_3c[-1];
        } while ((local_61 != '/') && (local_3c = pcVar12, local_61 != '\\'));
        local_3c = pcVar12;
      }
    }
    else {
      local_61 = *local_3c;
    }
LAB_00402879:
    if ((local_61 == '/') || (local_61 == '\\')) {
      do {
        cVar5 = local_61;
        local_3c = local_3c + 1;
        local_61 = *local_3c;
      } while (local_61 == '/' || local_61 == '\\');
      local_61 = cVar5;
      local_60 = local_30;
    }
    else {
      local_61 = '\\';
      local_60 = local_30;
    }
  }
  else {
    iVar8 = 2;
    pcVar12 = local_30;
    pcVar17 = ".";
    do {
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      bVar26 = *pcVar12 == *pcVar17;
      pcVar12 = pcVar12 + 1;
      pcVar17 = pcVar17 + 1;
    } while (bVar26);
    if (!bVar26) goto LAB_0040281b;
    if ((local_34 & 0x10) != 0) {
      *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402f14;
      local_38 = (char *)_text(iVar8,uVar6);
      if (local_38 == (char *)0x0) {
        *(char **)(&stack0xffffff84 + iVar11) = in_EAX;
        *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402f29;
        _strlen(*(char **)(&stack0xffffff84 + iVar11));
        *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402f37;
        uVar6 = ___chkstk_ms((&stack0xffffff84)[iVar11]);
        iVar8 = -uVar6;
        pcVar12 = acStack_70 + iVar8 + iVar11;
        do {
          cVar5 = *in_EAX;
          if (cVar5 == '\x7f') {
            cVar5 = in_EAX[1];
            in_EAX = in_EAX + 1;
          }
          in_EAX = in_EAX + 1;
          *pcVar12 = cVar5;
          pcVar12 = pcVar12 + 1;
        } while (cVar5 != '\0');
        *(char **)(&stack0xffffff84 + iVar8 + iVar11) = acStack_70 + iVar8 + iVar11;
        *(undefined4 *)((int)&pcStackY_80 + iVar8 + iVar11) = 0x402f66;
        pcVar12 = _strdup(*(char **)(&stack0xffffff84 + iVar8 + iVar11));
        ppvVar4 = (void **)(&stack0xffffff84 + iVar11);
        if ((pcVar12 == (char *)0x0) ||
           (ppvVar4 = (void **)(&stack0xffffff84 + iVar11), param_3 == (void *)0x0)) {
LAB_00402e8b:
          ppiVar20 = (int **)ppvVar4;
          local_48 = local_24;
        }
        else {
          *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402f83;
          FUN_004026a0(extraout_ECX_10,(int)param_3);
          local_48 = local_24;
        }
        goto LAB_00402dea;
      }
    }
    local_61 = '\\';
    local_60 = (char *)0x0;
    local_3c = in_EAX;
  }
  local_38 = (char *)0x2;
  local_48 = local_24;
  iVar8 = *local_24;
  local_30 = (char *)(local_34 & 0x8000);
  ppiVar20 = (int **)(&stack0xffffff84 + iVar11);
  ppcVar15 = (char **)(&stack0xffffff84 + iVar11);
  if (iVar8 != 0) {
LAB_004028d9:
    ppiVar20 = (int **)ppcVar15;
    *ppiVar20 = (int *)iVar8;
    ((char **)ppiVar20)[-1] = (char *)0x4028e1;
    puVar10 = ___mingw_opendir((char *)*ppiVar20);
    pcVar3 = local_40;
    if (puVar10 == (undefined4 *)0x0) {
      piVar25 = local_48;
      if ((local_34 & 4) != 0) {
LAB_00402db5:
        piVar19 = piVar25 + 1;
        *ppiVar20 = (int *)*piVar25;
        ppiVar20[-1] = (int *)0x402dbf;
        _free(*ppiVar20);
        if (piVar25[1] == 0) goto LAB_00402ddd;
LAB_00402dc6:
        iVar11 = local_48[1];
        do {
          piVar19 = piVar19 + 1;
          *ppiVar20 = (int *)iVar11;
          ppiVar20[-1] = (int *)0x402dd7;
          _free(*ppiVar20);
          iVar11 = *piVar19;
        } while (iVar11 != 0);
LAB_00402ddd:
        local_38 = (char *)0x1;
        local_48 = local_24;
        goto LAB_00402dea;
      }
      if (local_40 != (code *)0x0) {
        ((char **)ppiVar20)[-1] = (char *)0x402ea6;
        ppcVar15 = (char **)__errno();
        ((char **)ppiVar20)[1] = *ppcVar15;
        piVar25 = local_48;
        *ppiVar20 = (int *)*local_48;
        ppcVar21 = (char **)ppiVar20 + -1;
        ppiVar20 = (int **)((char **)ppiVar20 + -1);
        *ppcVar21 = (char *)0x402eb6;
        iVar11 = (*pcVar3)();
        if (iVar11 != 0) goto LAB_00402db5;
      }
    }
    else {
      if (local_60 == (char *)0x0) {
        local_44 = (undefined *)0x0;
        pvVar7 = extraout_ECX_00;
      }
      else {
        *ppiVar20 = (int *)*local_48;
        ((char **)ppiVar20)[-1] = (char *)0x402903;
        local_44 = (undefined *)_strlen((char *)*ppiVar20);
        pvVar7 = extraout_ECX_01;
      }
      local_4c = (undefined4 *)0x0;
      local_58 = local_44 + 2;
      ppcVar15 = (char **)ppiVar20;
LAB_00402920:
      ppiVar20 = (int **)ppcVar15;
      *ppiVar20 = puVar10;
      ppiVar20[-1] = (int *)0x402928;
      iVar11 = ___mingw_readdir(pvVar7,(int)*ppiVar20);
      uVar6 = local_34;
      if (iVar11 != 0) {
        ppcVar15 = (char **)ppiVar20;
        if ((local_30 == (char *)0x0) || (pvVar7 = extraout_ECX_02, *(int *)(iVar11 + 8) == 0x10)) {
          ppiVar20[-1] = (int *)0x40294f;
          iVar8 = FUN_00402480(uVar6,(char *)(iVar11 + 0xc));
          pvVar7 = extraout_ECX_03;
          if (iVar8 == 0) {
            local_54 = (undefined *)ppiVar20;
            ppiVar20[-1] = (int *)0x40296c;
            uVar6 = ___chkstk_ms(*(undefined *)ppiVar20);
            puVar13 = local_44;
            iVar8 = -uVar6;
            local_50 = (undefined4 *)0x0;
            pcVar12 = (char *)((int)ppiVar20 + iVar8 + 0xc);
            iVar16 = extraout_EDX_00;
            if (local_44 != (undefined *)0x0) {
              local_50 = (undefined4 *)extraout_EDX_00;
              iVar16 = *local_48;
              *(char **)((int)ppiVar20 + iVar8) = pcVar12;
              *(undefined **)((int)ppiVar20 + iVar8 + 8) = puVar13;
              *(int *)((int)ppiVar20 + iVar8 + 4) = iVar16;
              *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x402e1b;
              _memcpy(*(void **)((int)ppiVar20 + iVar8),*(void **)((int)ppiVar20 + iVar8 + 4),
                      *(size_t *)((int)ppiVar20 + iVar8 + 8));
              iVar16 = (int)local_50;
              if ((local_44[(int)((int)ppiVar20 + iVar8 + 0xb)] == '/') ||
                 (local_44[(int)((int)ppiVar20 + iVar8 + 0xb)] == '\\')) {
                local_50 = (undefined4 *)local_44;
              }
              else {
                local_50 = (undefined4 *)(local_44 + 1);
                pcVar12[(int)local_44] = local_61;
              }
            }
            puVar13 = (undefined *)local_50;
            *(char **)((int)ppiVar20 + iVar8 + 4) = (char *)(iVar11 + 0xc);
            *(int *)((int)ppiVar20 + iVar8 + 8) = iVar16 + 1;
            *(undefined **)((int)ppiVar20 + iVar8) = puVar13 + (int)pcVar12;
            *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x40299e;
            _memcpy(*(void **)((int)ppiVar20 + iVar8),*(void **)((int)ppiVar20 + iVar8 + 4),
                    *(size_t *)((int)ppiVar20 + iVar8 + 8));
            *(char **)((int)ppiVar20 + iVar8) = pcVar12;
            *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x4029a6;
            _strlen(*(char **)((int)ppiVar20 + iVar8));
            *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x4029b4;
            uVar6 = ___chkstk_ms(*(undefined *)((int)ppiVar20 + iVar8));
            iVar11 = -uVar6;
            pcVar17 = (char *)((int)ppiVar20 + iVar11 + iVar8 + 0xc);
            pcVar22 = pcVar17;
            do {
              while (cVar5 = *pcVar12, cVar5 != '\x7f') {
                pcVar12 = pcVar12 + 1;
                *pcVar22 = cVar5;
                pcVar22 = pcVar22 + 1;
                if (cVar5 == '\0') goto LAB_004029e9;
              }
              cVar5 = pcVar12[1];
              pcVar12 = pcVar12 + 2;
              *pcVar22 = cVar5;
              pcVar22 = pcVar22 + 1;
            } while (cVar5 != '\0');
LAB_004029e9:
            *(char **)((int)ppiVar20 + iVar11 + iVar8) = pcVar17;
            *(undefined4 *)((int)ppiVar20 + iVar11 + iVar8 + -4) = 0x4029f1;
            pcVar12 = _strdup(*(char **)((int)ppiVar20 + iVar11 + iVar8));
            ppcVar15 = (char **)local_54;
            if (pcVar12 == (char *)0x0) {
              local_38 = (char *)0x3;
              pvVar7 = extraout_ECX_04;
              goto LAB_00402920;
            }
            local_38 = (char *)((uint)local_38 & (local_38 == (char *)0x2) - 1);
            if ((local_34 & 0x40) == 0) {
              if (local_4c == (undefined4 *)0x0) {
                *(undefined4 *)((int)ppiVar20 + iVar8) = 0xc;
                *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x402ee1;
                puVar14 = (undefined4 *)_malloc(*(size_t *)((int)ppiVar20 + iVar8));
                pvVar7 = extraout_ECX_09;
                ppcVar15 = (char **)local_54;
                if (puVar14 == (undefined4 *)0x0) goto LAB_00402920;
                puVar14[2] = pcVar12;
                puVar14[1] = 0;
                *puVar14 = 0;
                pvVar7 = extraout_ECX_09;
              }
              else {
                uVar6 = local_34 & 0x4000;
                local_50 = puVar10;
                puVar14 = local_4c;
                do {
                  puVar18 = puVar14;
                  uVar1 = puVar18[2];
                  *(char **)((int)ppiVar20 + iVar8) = pcVar12;
                  *(undefined4 *)((int)ppiVar20 + iVar8 + 4) = uVar1;
                  if (uVar6 == 0) {
                    *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x402a5a;
                    puVar13 = (undefined *)
                              _stricoll(*(char **)((int)ppiVar20 + iVar8),
                                        *(char **)((int)ppiVar20 + iVar8 + 4));
                    puVar14 = (undefined4 *)*puVar18;
                    puVar2 = (undefined4 *)puVar18[1];
                    puVar10 = local_50;
                  }
                  else {
                    *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x402a38;
                    puVar13 = (undefined *)
                              _strcoll(*(char **)((int)ppiVar20 + iVar8),
                                       *(char **)((int)ppiVar20 + iVar8 + 4));
                    puVar14 = (undefined4 *)*puVar18;
                    puVar2 = (undefined4 *)puVar18[1];
                    puVar10 = local_50;
                  }
                  if (0 < (int)puVar13) {
                    puVar14 = puVar2;
                  }
                  local_50 = puVar10;
                } while (puVar14 != (undefined4 *)0x0);
                local_50 = (undefined4 *)puVar13;
                *(undefined4 *)((int)ppiVar20 + iVar8) = 0xc;
                *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x402a7b;
                puVar14 = (undefined4 *)_malloc(*(size_t *)((int)ppiVar20 + iVar8));
                pvVar7 = extraout_ECX_05;
                ppcVar15 = (char **)local_54;
                if (puVar14 == (undefined4 *)0x0) goto LAB_00402920;
                puVar14[2] = pcVar12;
                puVar14[1] = 0;
                *puVar14 = 0;
                if (0 < (int)local_50) {
                  puVar18[1] = puVar14;
                  pvVar7 = extraout_ECX_05;
                  goto LAB_00402920;
                }
                *puVar18 = puVar14;
                pvVar7 = extraout_ECX_05;
                if (local_4c != (undefined4 *)0x0) goto LAB_00402920;
              }
              local_4c = puVar14;
              ppcVar15 = (char **)local_54;
              goto LAB_00402920;
            }
            pvVar7 = param_3;
            if (param_3 != (void *)0x0) {
              *(undefined4 *)((int)ppiVar20 + iVar8 + -4) = 0x402e65;
              FUN_004026a0(param_3,(int)param_3);
              pvVar7 = extraout_ECX_08;
              ppcVar15 = (char **)local_54;
            }
          }
        }
        goto LAB_00402920;
      }
      *ppiVar20 = puVar10;
      ppiVar20[-1] = (int *)0x402d4b;
      ___mingw_closedir(*ppiVar20);
      if (local_4c != (undefined4 *)0x0) {
        ppiVar20[-1] = (int *)0x402d5d;
        FUN_00402700(extraout_ECX_07,(int)param_3);
      }
    }
    piVar25 = local_48;
    piVar19 = local_48 + 1;
    *ppiVar20 = (int *)*local_48;
    ppiVar20[-1] = (int *)0x402d6e;
    _free(*ppiVar20);
    iVar8 = piVar25[1];
    ppvVar4 = ppiVar20;
    if (iVar8 == 0) goto LAB_00402e8b;
    if (local_38 == (char *)0x1) goto LAB_00402dc6;
    local_48 = piVar19;
    ppcVar15 = (char **)ppiVar20;
    goto LAB_004028d9;
  }
LAB_00402dea:
  *ppiVar20 = local_48;
  ppiVar20[-1] = (int *)0x402df5;
  _free(*ppiVar20);
  return (uint)local_38;
  while (iVar8 = iVar8 + -1, iVar8 != 0) {
LAB_00402bf0:
    cVar5 = pcVar24[1];
    pcVar12 = pcVar24 + 1;
    if (cVar5 == '\x7f') {
      cVar5 = pcVar24[2];
      pcVar24 = pcVar12;
      while( true ) {
        if (cVar5 == '\0') goto LAB_00402c90;
        cVar5 = pcVar24[2];
        pcVar12 = pcVar24 + 2;
        if (cVar5 != '\x7f') break;
        cVar5 = pcVar24[3];
        pcVar24 = pcVar12;
      }
    }
    pcVar24 = pcVar12;
    if (cVar5 == '{') {
      iVar8 = iVar8 + 1;
      goto LAB_00402bf0;
    }
    if (cVar5 != '}') {
      if (cVar5 == '\0') {
LAB_00402c90:
        *pcVar22 = '\0';
        return 1;
      }
      goto LAB_00402bf0;
    }
  }
LAB_00402c33:
  pcVar24 = pcVar12 + 1;
  cVar5 = pcVar12[1];
  while( true ) {
    pcVar24 = pcVar24 + 1;
    *pcVar22 = cVar5;
    if (cVar5 == '\0') break;
    cVar5 = *pcVar24;
    pcVar22 = pcVar22 + 1;
  }
  *(void **)(&stack0xffffff84 + iVar11) = param_3;
  uVar6 = local_34;
  pcVar3 = local_40;
  uVar23 = local_34 | 1;
  *(undefined4 *)((int)&pcStackY_80 + iVar11) = 0x402c69;
  uVar6 = FUN_00402750(pcVar3,uVar6,*(void **)(&stack0xffffff84 + iVar11));
  local_34 = uVar23;
  if (uVar6 == 1) {
    return 1;
  }
  if (*pcVar17 != ',') {
    return uVar6;
  }
  goto LAB_00402b35;
}

// Function: ___mingw_glob
/* WARNING: Unable to track spacebase fully for stack */

uint __cdecl ___mingw_glob(char *param_1,uint param_2,undefined *param_3,char **param_4)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  uint uVar4;
  char *pcVar5;
  undefined4 uStackY_40;
  char acStack_38 [20];
  uint local_24;
  undefined *local_20;
  
  if ((param_4 != (char **)0x0) && ((param_2 & 2) == 0)) {
    param_4[3] = (char *)0x0;
  }
  if (*param_4 != "glob-1.0-mingw32") {
    uStackY_40 = 0x40300d;
    FUN_00402150();
    *param_4 = "glob-1.0-mingw32";
  }
  uStackY_40 = 0x403022;
  local_24 = FUN_00402750(param_3,param_2,param_4);
  if ((local_24 == 2) && ((param_2 & 0x10) != 0)) {
    uStackY_40 = 0x403053;
    pcVar5 = param_1;
    local_20 = &stack0xffffffc4;
    _strlen(param_1);
    uStackY_40 = 0x403061;
    uVar4 = ___chkstk_ms((char)pcVar5);
    iVar2 = -uVar4;
    pcVar5 = acStack_38 + iVar2;
    do {
      while (cVar1 = *param_1, cVar1 == '\x7f') {
        cVar1 = param_1[1];
        param_1 = param_1 + 2;
        *pcVar5 = cVar1;
        pcVar5 = pcVar5 + 1;
        if (cVar1 == '\0') goto LAB_00403098;
      }
      param_1 = param_1 + 1;
      *pcVar5 = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
LAB_00403098:
    *(char **)(&stack0xffffffc4 + iVar2) = acStack_38 + iVar2;
    *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x4030a3;
    pcVar5 = _strdup(*(char **)(&stack0xffffffc4 + iVar2));
    puVar3 = local_20;
    uVar4 = local_24;
    if (pcVar5 != (char *)0x0) {
      local_20 = (undefined *)local_24;
      *(undefined4 *)(puVar3 + -4) = 0x4030bb;
      FUN_004026a0(uVar4,(int)param_4);
      local_24 = (uint)local_20;
    }
  }
  return local_24;
}

// Function: ___mingw_dirname
/* WARNING: Unable to track spacebase fully for stack */

char * __cdecl ___mingw_dirname(char *param_1)

{
  short *psVar1;
  int iVar2;
  char *_Src;
  size_t sVar3;
  uint uVar4;
  short *psVar5;
  short *psVar6;
  short *psVar7;
  short *psVar8;
  short sVar9;
  undefined4 extraout_EDX;
  undefined4 uStackY_40;
  undefined uVar10;
  short asStack_30 [2];
  size_t local_2c;
  undefined *local_28;
  short local_22;
  short *local_20;
  
  uStackY_40 = 0x40314d;
  _Src = _setlocale(2,(char *)0x0);
  if (_Src != (char *)0x0) {
    uStackY_40 = 0x40315b;
    _Src = _strdup(_Src);
  }
  uStackY_40 = 0x403171;
  _setlocale(2,"");
  if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
LAB_00403180:
    uStackY_40 = 0x40319c;
    sVar3 = _wcstombs((char *)0x0,L".",0);
    uStackY_40 = 0x4031b0;
    _bss = (char *)_realloc(_bss,sVar3 + 1);
    uStackY_40 = 0x4031c9;
    _wcstombs(_bss,L".",sVar3 + 1);
    uStackY_40 = 0x4031d9;
    _setlocale(2,_Src);
    uStackY_40 = 0x4031e1;
    _free(_Src);
    return _bss;
  }
  uVar10 = 0;
  uStackY_40 = 0x40320f;
  local_28 = &stack0xffffffc4;
  _mbstowcs((wchar_t *)0x0,param_1,0);
  uStackY_40 = 0x403220;
  uVar4 = ___chkstk_ms(uVar10);
  iVar2 = -uVar4;
  *(undefined4 *)(&stack0xffffffcc + iVar2) = extraout_EDX;
  psVar1 = (short *)((int)asStack_30 + iVar2);
  *(short **)(&stack0xffffffc4 + iVar2) = psVar1;
  *(char **)(&stack0xffffffc8 + iVar2) = param_1;
  *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x403239;
  sVar3 = _mbstowcs(*(wchar_t **)(&stack0xffffffc4 + iVar2),*(char **)(&stack0xffffffc8 + iVar2),
                    *(size_t *)(&stack0xffffffcc + iVar2));
  local_2c = sVar3;
  psVar1[sVar3] = 0;
  local_22 = *psVar1;
  local_20 = psVar1;
  if (1 < sVar3) {
    if ((local_22 == 0x2f) || (local_22 == 0x5c)) {
      if ((local_22 == *(short *)((int)asStack_30 + iVar2 + 2)) &&
         (*(short *)((int)&local_2c + iVar2) == 0)) {
        *(char **)(&stack0xffffffc8 + iVar2) = _Src;
        *(undefined4 *)(&stack0xffffffc4 + iVar2) = 2;
        *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x4034a0;
        _setlocale(*(int *)(&stack0xffffffc4 + iVar2),*(char **)(&stack0xffffffc8 + iVar2));
        *(char **)(&stack0xffffffc4 + iVar2) = _Src;
        *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x4034a8;
        _free(*(void **)(&stack0xffffffc4 + iVar2));
        return param_1;
      }
    }
    else if (*(short *)((int)asStack_30 + iVar2 + 2) == 0x3a) {
      local_20 = (short *)((int)&local_2c + iVar2);
      local_22 = *(short *)((int)&local_2c + iVar2);
    }
  }
  psVar6 = local_20;
  psVar8 = local_20;
  psVar7 = local_20;
  sVar9 = local_22;
  if (local_22 == 0) goto LAB_00403180;
  do {
    while ((psVar5 = psVar8, sVar9 == 0x2f || (sVar9 == 0x5c))) {
      sVar9 = *psVar5;
      if (sVar9 != 0x2f) goto LAB_004032c1;
      do {
        do {
          psVar5 = psVar5 + 1;
          sVar9 = *psVar5;
        } while (sVar9 == 0x2f);
LAB_004032c1:
      } while (sVar9 == 0x5c);
      if (sVar9 == 0) goto LAB_004032da;
      psVar8 = psVar5 + 1;
      psVar7 = psVar5;
      sVar9 = psVar5[1];
      if (psVar5[1] == 0) goto LAB_004032da;
    }
    psVar8 = psVar5 + 1;
    sVar9 = psVar5[1];
  } while (psVar5[1] != 0);
LAB_004032da:
  if (psVar7 <= local_20) {
    if ((local_22 != 0x2f) && (local_22 != 0x5c)) {
      *local_20 = 0x2e;
    }
    psVar6[1] = 0;
    *(undefined4 *)(&stack0xffffffcc + iVar2) = 0;
    *(short **)(&stack0xffffffc8 + iVar2) = psVar1;
    *(undefined4 *)(&stack0xffffffc4 + iVar2) = 0;
    *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x403328;
    sVar3 = _wcstombs(*(char **)(&stack0xffffffc4 + iVar2),*(wchar_t **)(&stack0xffffffc8 + iVar2),
                      *(size_t *)(&stack0xffffffcc + iVar2));
    *(short **)(&stack0xffffffc8 + iVar2) = (short *)(sVar3 + 1);
    local_20 = (short *)(sVar3 + 1);
    *(char **)(&stack0xffffffc4 + iVar2) = _bss;
    *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x40333f;
    param_1 = (char *)_realloc(*(void **)(&stack0xffffffc4 + iVar2),
                               *(size_t *)(&stack0xffffffc8 + iVar2));
    psVar6 = local_20;
    *(short **)(&stack0xffffffc8 + iVar2) = psVar1;
    *(char **)(&stack0xffffffc4 + iVar2) = param_1;
    *(short **)(&stack0xffffffcc + iVar2) = psVar6;
    *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x403359;
    _bss = param_1;
    _wcstombs(*(char **)(&stack0xffffffc4 + iVar2),*(wchar_t **)(&stack0xffffffc8 + iVar2),
              *(size_t *)(&stack0xffffffcc + iVar2));
    goto LAB_00403420;
  }
  do {
    psVar6 = psVar7 + -1;
    if (psVar6 <= local_20) {
      if ((local_20 == psVar6) &&
         ((((local_22 == 0x2f || (local_22 == 0x5c)) && (*psVar7 == local_22)) &&
          ((psVar7[1] != 0x2f && (psVar7[1] != 0x5c)))))) {
        psVar6 = psVar7;
      }
      break;
    }
    psVar8 = psVar7 + -1;
    psVar7 = psVar6;
  } while ((*psVar8 == 0x2f) || (*psVar8 == 0x5c));
  psVar6[1] = 0;
  sVar9 = *psVar1;
  psVar7 = psVar1;
  psVar6 = psVar1;
  psVar8 = psVar1;
  if ((sVar9 == 0x2f) || (sVar9 == 0x5c)) {
    do {
      do {
        psVar7 = psVar7 + 1;
      } while (*psVar7 == 0x2f);
    } while (*psVar7 == 0x5c);
    if ((int)psVar7 - (int)psVar1 < 6) goto LAB_004034ad;
  }
  else {
LAB_004034ad:
    if (*(short *)((int)asStack_30 + iVar2 + 2) == sVar9) {
      sVar9 = *psVar7;
      psVar6 = psVar7;
      psVar8 = psVar7;
    }
  }
  while (psVar7 = psVar6, psVar6 = psVar8, sVar9 != 0) {
    while( true ) {
      psVar8 = psVar6 + 1;
      *psVar6 = sVar9;
      psVar6 = psVar7;
      if ((sVar9 == 0x2f) || (psVar6 = psVar7 + 1, *psVar7 == 0x5c)) break;
      sVar9 = psVar7[1];
      psVar7 = psVar6;
      psVar6 = psVar8;
      if (sVar9 == 0) goto LAB_004033f9;
    }
    sVar9 = *psVar6;
    if ((sVar9 == 0x5c) || (sVar9 == 0x2f)) {
      do {
        do {
          psVar6 = psVar6 + 1;
          sVar9 = *psVar6;
        } while (sVar9 == 0x2f);
      } while (sVar9 == 0x5c);
    }
  }
LAB_004033f9:
  sVar3 = local_2c;
  *psVar8 = 0;
  *(short **)(&stack0xffffffc8 + iVar2) = psVar1;
  *(size_t *)(&stack0xffffffcc + iVar2) = sVar3;
  *(char **)(&stack0xffffffc4 + iVar2) = param_1;
  *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x403414;
  sVar3 = _wcstombs(*(char **)(&stack0xffffffc4 + iVar2),*(wchar_t **)(&stack0xffffffc8 + iVar2),
                    *(size_t *)(&stack0xffffffcc + iVar2));
  if (sVar3 != 0xffffffff) {
    param_1[sVar3] = '\0';
  }
LAB_00403420:
  *(char **)(&stack0xffffffc8 + iVar2) = _Src;
  *(undefined4 *)(&stack0xffffffc4 + iVar2) = 2;
  *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x403430;
  _setlocale(*(int *)(&stack0xffffffc4 + iVar2),*(char **)(&stack0xffffffc8 + iVar2));
  *(char **)(&stack0xffffffc4 + iVar2) = _Src;
  *(undefined4 *)((int)&uStackY_40 + iVar2) = 0x403438;
  _free(*(void **)(&stack0xffffffc4 + iVar2));
  return param_1;
}

// Function: .text
HANDLE __fastcall _text(undefined4 param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  LPCSTR in_EAX;
  HANDLE pvVar3;
  DWORD *pDVar4;
  DWORD DVar5;
  int *piVar6;
  char *pcVar7;
  _WIN32_FIND_DATAA local_14c;
  
  pvVar3 = _FindFirstFileA_8(in_EAX,&local_14c);
  if (pvVar3 == (HANDLE)0xffffffff) {
    pDVar4 = (DWORD *)__errno();
    DVar5 = _GetLastError_0();
    *pDVar4 = DVar5;
    if (DVar5 == 3) {
      piVar6 = __errno();
      *piVar6 = 2;
    }
    else {
      piVar6 = __errno();
      if (*piVar6 == 0x10b) {
        piVar6 = __errno();
        *piVar6 = 0x14;
      }
      else {
        piVar6 = __errno();
        if (*piVar6 != 2) {
          piVar6 = __errno();
          *piVar6 = 0x16;
        }
      }
    }
  }
  else {
    pcVar7 = (char *)(param_2 + 0xc);
    *(undefined2 *)(param_2 + 6) = 0;
    uVar2 = 0;
    while (cVar1 = local_14c.cFileName[uVar2], *pcVar7 = cVar1, cVar1 != '\0') {
      uVar2 = *(short *)(param_2 + 6) + 1;
      *(ushort *)(param_2 + 6) = uVar2;
      pcVar7 = pcVar7 + (uVar2 < 0x104);
    }
    if ((local_14c.dwFileAttributes & 0xffffff58) < 0x11) {
      *(DWORD *)(param_2 + 8) = local_14c.dwFileAttributes & 0xffffff58;
      return pvVar3;
    }
    *(undefined4 *)(param_2 + 8) = 0x18;
  }
  return pvVar3;
}

// Function: FUN_00403600
BOOL __fastcall FUN_00403600(undefined4 param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  HANDLE in_EAX;
  BOOL BVar3;
  DWORD DVar4;
  int *piVar5;
  char *pcVar6;
  _WIN32_FIND_DATAA local_14c;
  
  BVar3 = _FindNextFileA_8(in_EAX,&local_14c);
  if (BVar3 == 0) {
    DVar4 = _GetLastError_0();
    if (DVar4 != 0x12) {
      piVar5 = __errno();
      *piVar5 = 2;
      return 0;
    }
  }
  else {
    pcVar6 = (char *)(param_2 + 0xc);
    *(undefined2 *)(param_2 + 6) = 0;
    uVar2 = 0;
    while (cVar1 = local_14c.cFileName[uVar2], *pcVar6 = cVar1, cVar1 != '\0') {
      uVar2 = *(short *)(param_2 + 6) + 1;
      *(ushort *)(param_2 + 6) = uVar2;
      pcVar6 = pcVar6 + (uVar2 < 0x104);
    }
    if (0x10 < (local_14c.dwFileAttributes & 0xffffff58)) {
      *(undefined4 *)(param_2 + 8) = 0x18;
      return BVar3;
    }
    *(DWORD *)(param_2 + 8) = local_14c.dwFileAttributes & 0xffffff58;
  }
  return BVar3;
}

// Function: ___mingw_opendir
undefined4 * __cdecl ___mingw_opendir(char *param_1)

{
  int iVar1;
  char *pcVar2;
  uint *puVar3;
  undefined4 *_Memory;
  HANDLE pvVar4;
  int *piVar5;
  undefined4 extraout_ECX;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  char local_120;
  
  if (param_1 == (char *)0x0) {
    piVar5 = __errno();
    _Memory = (undefined4 *)0x0;
    *piVar5 = 0x16;
  }
  else if (*param_1 == '\0') {
    piVar5 = __errno();
    _Memory = (undefined4 *)0x0;
    *piVar5 = 2;
  }
  else {
    __fullpath(&local_120,param_1,0x104);
    puVar8 = (uint *)&local_120;
    if (local_120 == '\0') {
      do {
        puVar3 = puVar8;
        puVar8 = puVar3 + 1;
        uVar6 = *puVar3 + 0xfefefeff & ~*puVar3;
        uVar7 = uVar6 & 0x80808080;
      } while (uVar7 == 0);
      if ((uVar6 & 0x8080) == 0) {
        uVar7 = uVar7 >> 0x10;
        puVar8 = (uint *)((int)puVar3 + 6);
      }
      pcVar2 = (char *)((int)puVar8 +
                       ((-3 - (uint)CARRY1((byte)uVar7,(byte)uVar7)) - (int)&local_120));
    }
    else {
      do {
        puVar3 = puVar8;
        puVar8 = puVar3 + 1;
        uVar6 = *puVar3 + 0xfefefeff & ~*puVar3;
        uVar7 = uVar6 & 0x80808080;
      } while (uVar7 == 0);
      if ((uVar6 & 0x8080) == 0) {
        uVar7 = uVar7 >> 0x10;
        puVar8 = (uint *)((int)puVar3 + 6);
      }
      pcVar2 = (char *)((int)puVar8 +
                       ((-3 - (uint)CARRY1((byte)uVar7,(byte)uVar7)) - (int)&local_120));
      if (((&stack0xfffffedc)[(int)(pcVar2 + 3)] != '/') &&
         ((&stack0xfffffedc)[(int)(pcVar2 + 3)] != '\\')) {
        *(undefined2 *)((int)&local_120 + (int)pcVar2) = 0x5c;
        pcVar2 = pcVar2 + 1;
      }
    }
    *(undefined2 *)((int)&local_120 + (int)pcVar2) = 0x2a;
    puVar8 = (uint *)&local_120;
    do {
      puVar3 = puVar8;
      puVar8 = puVar3 + 1;
      uVar6 = *puVar3 + 0xfefefeff & ~*puVar3;
      uVar7 = uVar6 & 0x80808080;
    } while (uVar7 == 0);
    if ((uVar6 & 0x8080) == 0) {
      uVar7 = uVar7 >> 0x10;
      puVar8 = (uint *)((int)puVar3 + 6);
    }
    iVar1 = (-3 - (uint)CARRY1((byte)uVar7,(byte)uVar7)) - (int)&local_120;
    _Memory = (undefined4 *)_malloc((size_t)((int)puVar8 + iVar1 + 0x11c));
    if (_Memory == (undefined4 *)0x0) {
      piVar5 = __errno();
      *piVar5 = 0xc;
    }
    else {
      _memcpy(_Memory + 0x46,&local_120,(size_t)((int)puVar8 + iVar1 + 1));
      pvVar4 = _text(extraout_ECX,(int)_Memory);
      _Memory[0x44] = pvVar4;
      if (pvVar4 == (HANDLE)0xffffffff) {
        _free(_Memory);
        _Memory = (undefined4 *)0x0;
      }
      else {
        _Memory[0x45] = 0;
        *_Memory = 0;
        *(undefined2 *)(_Memory + 1) = 0x110;
      }
    }
  }
  return _Memory;
}

// Function: ___mingw_readdir
int __thiscall ___mingw_readdir(void *this,int param_1)

{
  int iVar1;
  BOOL BVar2;
  int *piVar3;
  
  if (param_1 == 0) {
    piVar3 = __errno();
    *piVar3 = 9;
    param_1 = 0;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x114);
    *(int *)(param_1 + 0x114) = iVar1 + 1;
    if ((0 < iVar1) && (BVar2 = FUN_00403600(this,param_1), BVar2 == 0)) {
      return 0;
    }
  }
  return param_1;
}

// Function: ___mingw_closedir
undefined4 __cdecl ___mingw_closedir(void *param_1)

{
  BOOL BVar1;
  int *piVar2;
  
  if ((param_1 != (void *)0x0) &&
     (BVar1 = _FindClose_4(*(HANDLE *)((int)param_1 + 0x110)), BVar1 != 0)) {
    _free(param_1);
    return 0;
  }
  piVar2 = __errno();
  *piVar2 = 9;
  return 0xffffffff;
}

// Function: ___mingw_rewinddir
void __cdecl ___mingw_rewinddir(int param_1)

{
  BOOL BVar1;
  int *piVar2;
  HANDLE pvVar3;
  undefined4 extraout_ECX;
  
  if ((param_1 != 0) && (BVar1 = _FindClose_4(*(HANDLE *)(param_1 + 0x110)), BVar1 != 0)) {
    pvVar3 = _text(extraout_ECX,param_1);
    *(HANDLE *)(param_1 + 0x110) = pvVar3;
    if (pvVar3 == (HANDLE)0xffffffff) {
      return;
    }
    *(undefined4 *)(param_1 + 0x114) = 0;
    return;
  }
  piVar2 = __errno();
  *piVar2 = 9;
  return;
}

// Function: _wcstombs
size_t __cdecl _wcstombs(char *_Dest,wchar_t *_Source,size_t _MaxCount)

{
  size_t sVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sVar1 = wcstombs(_Dest,_Source,_MaxCount);
  return sVar1;
}

// Function: _vfprintf
int __cdecl _vfprintf(FILE *_File,char *_Format,va_list _ArgList)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = vfprintf(_File,_Format,_ArgList);
  return iVar1;
}

// Function: _tolower
int __cdecl _tolower(int _C)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = tolower(_C);
  return iVar1;
}

// Function: _strlen
size_t __cdecl _strlen(char *_Str)

{
  size_t sVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sVar1 = strlen(_Str);
  return sVar1;
}

// Function: _strcoll
int __cdecl _strcoll(char *_Str1,char *_Str2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = strcoll(_Str1,_Str2);
  return iVar1;
}

// Function: _signal
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _signal(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00403a48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  signal(param_1);
  return;
}

// Function: _setlocale
char * __cdecl _setlocale(int _Category,char *_Locale)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = setlocale(_Category,_Locale);
  return pcVar1;
}

// Function: _realloc
void * __cdecl _realloc(void *_Memory,size_t _NewSize)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = realloc(_Memory,_NewSize);
  return pvVar1;
}

// Function: _puts
int __cdecl _puts(char *_Str)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = puts(_Str);
  return iVar1;
}

// Function: _memcpy
void * __cdecl _memcpy(void *_Dst,void *_Src,size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memcpy(_Dst,_Src,_Size);
  return pvVar1;
}

// Function: _mbstowcs
size_t __cdecl _mbstowcs(wchar_t *_Dest,char *_Source,size_t _MaxCount)

{
  size_t sVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sVar1 = mbstowcs(_Dest,_Source,_MaxCount);
  return sVar1;
}

// Function: _malloc
void * __cdecl _malloc(size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = malloc(_Size);
  return pvVar1;
}

// Function: _fwrite
size_t __cdecl _fwrite(void *_Str,size_t _Size,size_t _Count,FILE *_File)

{
  size_t sVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sVar1 = fwrite(_Str,_Size,_Count,_File);
  return sVar1;
}

// Function: _free
void __cdecl _free(void *_Memory)

{
                    /* WARNING: Could not recover jumptable at 0x00403a88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(_Memory);
  return;
}

// Function: _calloc
void * __cdecl _calloc(size_t _Count,size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403a90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = calloc(_Count,_Size);
  return pvVar1;
}

// Function: _abort
void __cdecl _abort(void)

{
                    /* WARNING: Could not recover jumptable at 0x00403a98. Too many branches */
                    /* WARNING: Subroutine does not return */
                    /* WARNING: Treating indirect jump as call */
  abort();
  return;
}

// Function: __setmode
int __cdecl __setmode(int _FileHandle,int _Mode)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403aa0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = _setmode(_FileHandle,_Mode);
  return iVar1;
}

// Function: __isctype
int __cdecl __isctype(int _C,int _Type)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403aa8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = _isctype(_C,_Type);
  return iVar1;
}

// Function: __fullpath
char * __cdecl __fullpath(char *_FullPath,char *_Path,size_t _SizeInBytes)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403ab0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = _fullpath(_FullPath,_Path,_SizeInBytes);
  return pcVar1;
}

// Function: __errno
int * __cdecl __errno(void)

{
  int *piVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403ab8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  piVar1 = _errno();
  return piVar1;
}

// Function: __cexit
void __cdecl __cexit(void)

{
                    /* WARNING: Could not recover jumptable at 0x00403ac0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _cexit();
  return;
}

// Function: ___p__fmode
void ___p__fmode(void)

{
                    /* WARNING: Could not recover jumptable at 0x00403ac8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  __p__fmode();
  return;
}

// Function: ___p__environ
void ___p__environ(void)

{
                    /* WARNING: Could not recover jumptable at 0x00403ad0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  __p__environ();
  return;
}

// Function: ___getmainargs
int __cdecl
___getmainargs(int *_Argc,char ***_Argv,char ***_Env,int _DoWildCard,_startupinfo *_StartInfo)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403ad8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = __getmainargs(_Argc,_Argv,_Env,_DoWildCard,_StartInfo);
  return iVar1;
}

// Function: _VirtualQuery@12
SIZE_T _VirtualQuery_12(LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength)

{
  SIZE_T SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403ae0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = VirtualQuery(lpAddress,lpBuffer,dwLength);
  return SVar1;
}

// Function: _VirtualProtect@16
BOOL _VirtualProtect_16(LPVOID lpAddress,SIZE_T dwSize,DWORD flNewProtect,PDWORD lpflOldProtect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = VirtualProtect(lpAddress,dwSize,flNewProtect,lpflOldProtect);
  return BVar1;
}

// Function: _TlsGetValue@4
LPVOID _TlsGetValue_4(DWORD dwTlsIndex)

{
  LPVOID pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403af0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = TlsGetValue(dwTlsIndex);
  return pvVar1;
}

// Function: _SetUnhandledExceptionFilter@4
LPTOP_LEVEL_EXCEPTION_FILTER
_SetUnhandledExceptionFilter_4(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)

{
  LPTOP_LEVEL_EXCEPTION_FILTER pPVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403af8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pPVar1 = SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
  return pPVar1;
}

// Function: _LoadLibraryA@4
HMODULE _LoadLibraryA_4(LPCSTR lpLibFileName)

{
  HMODULE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadLibraryA(lpLibFileName);
  return pHVar1;
}

// Function: _LeaveCriticalSection@4
void _LeaveCriticalSection_4(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x00403b08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LeaveCriticalSection(lpCriticalSection);
  return;
}

// Function: _InitializeCriticalSection@4
void _InitializeCriticalSection_4(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x00403b10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  InitializeCriticalSection(lpCriticalSection);
  return;
}

// Function: _GetProcAddress@8
FARPROC _GetProcAddress_8(HMODULE hModule,LPCSTR lpProcName)

{
  FARPROC pFVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pFVar1 = GetProcAddress(hModule,lpProcName);
  return pFVar1;
}

// Function: _GetModuleHandleA@4
HMODULE _GetModuleHandleA_4(LPCSTR lpModuleName)

{
  HMODULE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetModuleHandleA(lpModuleName);
  return pHVar1;
}

// Function: _GetLastError@0
DWORD _GetLastError_0(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetLastError();
  return DVar1;
}

// Function: _GetCommandLineA@0
LPSTR _GetCommandLineA_0(void)

{
  LPSTR pCVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pCVar1 = GetCommandLineA();
  return pCVar1;
}

// Function: _FreeLibrary@4
BOOL _FreeLibrary_4(HMODULE hLibModule)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FreeLibrary(hLibModule);
  return BVar1;
}

// Function: _FindNextFileA@8
BOOL _FindNextFileA_8(HANDLE hFindFile,LPWIN32_FIND_DATAA lpFindFileData)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FindNextFileA(hFindFile,lpFindFileData);
  return BVar1;
}

// Function: _FindFirstFileA@8
HANDLE _FindFirstFileA_8(LPCSTR lpFileName,LPWIN32_FIND_DATAA lpFindFileData)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = FindFirstFileA(lpFileName,lpFindFileData);
  return pvVar1;
}

// Function: _FindClose@4
BOOL _FindClose_4(HANDLE hFindFile)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FindClose(hFindFile);
  return BVar1;
}

// Function: _ExitProcess@4
void _ExitProcess_4(UINT uExitCode)

{
                    /* WARNING: Could not recover jumptable at 0x00403b58. Too many branches */
                    /* WARNING: Subroutine does not return */
                    /* WARNING: Treating indirect jump as call */
  ExitProcess(uExitCode);
  return;
}

// Function: _EnterCriticalSection@4
void _EnterCriticalSection_4(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x00403b60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EnterCriticalSection(lpCriticalSection);
  return;
}

// Function: _DeleteCriticalSection@4
void _DeleteCriticalSection_4(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x00403b68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DeleteCriticalSection(lpCriticalSection);
  return;
}

// Function: _stricoll
int __cdecl _stricoll(char *_Str1,char *_Str2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = _stricoll(_Str1,_Str2);
  return iVar1;
}

// Function: _strdup
char * __cdecl _strdup(char *_Src)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00403b78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = _strdup(_Src);
  return pcVar1;
}

