//
// taskswitch.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2018  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __CONTEXT__
#define __CONTEXT__

#include <circle/macros.h>
#include <circle/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// see: "Procedure Call Standard for the ARM 64-bit Architecture (AArch64)"
struct TRegisters {
    u64 x28;
    u64 xzr;

    u64 x26;
    u64 x27;

    u64 x24; // callee-saved registers
    u64 x25;

    u64 x22;
    u64 x23;

    u64 x20;
    u64 x21;

    u64 x18;
    u64 x19;

    u64 x16;
    u64 x17;

    u64 x14;
    u64 x15;

    u64 x12;
    u64 x13;

    u64 x10;
    u64 x11;

    u64 x8;
    u64 x9;

    u64 x6;
    u64 x7;

    u64 x4; // unknown role (on this platform)
    u64 x5;

    u64 x2;
    u64 x3;

    u64 x0; // parameter for CTask::TaskEntry()
    u64 x1;

    u64 elr;  // link register
    u64 spsr; // link register

    u64 x29; // frame pointer
    u64 x30; // link register

    // u64 sp; // stack pointer

} PACKED;

struct TSysRegs {
    u64 esr;
    u64 spsr;
    u64 lr;
    u64 elr;
    u64 spel0;
    u64 sp;
    u64 far;

} PACKED;

typedef void (*run_func)();

class CProcess {
public:
    volatile u64* pTopStack;
    u64* pStack;
    CProcess()
    {
    }
    ~CProcess()
    {
    }
    virtual void Run()
    {
        return;
    }
    static void TaskEntry(void* pParam)
    {
        CProcess* p = (CProcess*)pParam;
        p->Run();
    }
};

class AProc : public CProcess {
public:
    AProc()
    {
    }
    ~AProc()
    {
    }
    void Run()
    {
        int i = 0;
        while (1) {
            CLogger::Get()->Write("A running", LogNotice, " ... Iteration - %d", i++);
            CTimer::Get()->MsDelay(1000);
        }
        return;
    }
};

void StoreContext(TRegisters* pRegs);
void LoadContext(TRegisters* pRegs);
void Switch();
void SaveRegs(TSysRegs* pRegs);
void SaveReg(volatile u64* reg);
void SContext(TRegisters* oldRegs, TRegisters* newRegs);

#ifdef __cplusplus
}
#endif

#endif
