#pragma once

/* ==== STRUCTS ===================*/

struct RefdefView {
    Vector2 tanHalfFov;		// 0x00
    uint8_t unk1[0xC];		// 0x08
    Vector3 axis[3];      // 0x14
};

struct refdef_t {
    int x;           // 0x00
    int y;           // 0x04
    int width;       // 0x08
    int height;      // 0x0C
    RefdefView view; // 0x10

    bool operator==(const refdef_t& v)
    {
        if (x == v.x && y == v.y && width == v.width && height == v.height && view.axis->x == v.view.axis->x && view.axis->y == v.view.axis->y && view.axis->z == v.view.axis->z && view.tanHalfFov.x == v.view.tanHalfFov.x && view.tanHalfFov.y == v.view.tanHalfFov.y && view.unk1 == v.view.unk1) {
            return true;
        }
        else {
            return false;
        }
    }
};

struct refdefKeyStruct
{
    DWORD ref0; // 0x00
    DWORD ref1; // 0x04
    DWORD ref2; // 0x08
};

struct NameEntry {
    uint32_t idx;
    char name[0x24];
    uint8_t unk1[0x64];
    uint32_t health;
};
/* =================================*/

bool is_bad_ptr(void* adr) { return adr == nullptr; }
bool IsValidPointer(void* addr) { return !is_bad_ptr(addr); }
namespace utils
{
    void log(const char* str)
    {
        std::cout << str << std::endl;
    }
}

namespace offsets
{
    constexpr auto Camera_Base = 0x157F5CD0;
    constexpr auto Camera_Pos = 0x1D8;
    constexpr auto Local_Index = 0x34D20;
    constexpr auto CLIENT_INFO = 0x1806E058;
    constexpr auto CLIENT_BASE = 0x9FDE8;
    constexpr auto Ref_Def = 0x18070A08;
    constexpr auto Dead_1 = 0x66C;
    constexpr auto Dead_2 = 0x5C8;
    constexpr auto Player_Pos_Info = 0x4F8;
    constexpr auto Player_Size = 0x3AB8;
    constexpr auto Player_Team = 0x3F0;
    constexpr auto Player_Valid = 0x544;
    constexpr auto Name_Array = 0x1807C248;
    constexpr auto Name_Array_Padding = 0x4C70;
    constexpr auto Name_Size = 0xD0;
    constexpr auto Bones_Distribute = 0x1A722978;
    constexpr auto Bones_Visible = 0x6198540;
    namespace bones
    {
        constexpr auto bone_base = 0x38E6C;
        constexpr auto size = 0x150;
    }
}


namespace decryption
{
    auto DecryptClientInfo(uint64_t enc_client) -> uint64_t
    {
        uint64_t RAX = No_Define::BaseAddress, RBX = No_Define::BaseAddress, RCX = No_Define::BaseAddress, RDX = No_Define::BaseAddress, R8 = No_Define::BaseAddress, RDI = No_Define::BaseAddress, RSI = No_Define::BaseAddress, R9 = No_Define::BaseAddress, R10 = No_Define::BaseAddress, R11 = No_Define::BaseAddress, R12 = No_Define::BaseAddress, R13 = No_Define::BaseAddress, R14 = No_Define::BaseAddress, R15 = No_Define::BaseAddress;
        RBX = enc_client;
        if (RBX == 0)
        {
            return 0;
        }
        uint64_t RSP_0x58 = No_Define::BaseAddress;
        RSP_0x58 = 0x3; // mov byte ptr [rsp+58h],3
        // movzx eax,byte ptr [rsp+58h]
        RAX = _rotl64(RAX, 0x5D);
        // movzx eax,al
        R8 = No_Define::PEB; // mov r8,gs:[rax]
        RAX = RBX;
        RAX >>= 0xD;
        RBX ^= RAX;
        RAX = RBX;
        RAX >>= 0x1A;
        RBX ^= RAX;
        RAX = 0x75AC52C47565F299;
        RDX = RBX;
        RDX >>= 0x34;
        RDX ^= RBX;
        RDX *= RAX;
        RAX = 0x3F38F2AE23228E30;
        RDX -= RAX;
        RAX = RDX;
        RAX >>= 0x7;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0xE;
        RDX ^= RAX;
        RAX = RDX;
        RAX >>= 0x1C;
        RDX ^= RAX;
        RAX = RDX;
        RCX = 0x0;
        RAX >>= 0x38;
        RCX = _rotl64(RCX, 0x10);
        RAX ^= RDX;
        RCX ^= *(uint64_t*)(No_Define::BaseAddress + 0x71D90F2);
        RCX = ~RCX;
        RBX = *(uint64_t*)(RCX + 0x13);
        RBX *= RAX;
        RBX -= R8;
        return RBX;
    }
    auto DecryptClientBase(uint64_t client_info) -> uint64_t
    {
        uint64_t RAX = No_Define::BaseAddress, RBX = No_Define::BaseAddress, RCX = No_Define::BaseAddress, RDX = No_Define::BaseAddress, R8 = No_Define::BaseAddress, RDI = No_Define::BaseAddress, RSI = No_Define::BaseAddress, R9 = No_Define::BaseAddress, R10 = No_Define::BaseAddress, R11 = No_Define::BaseAddress, R12 = No_Define::BaseAddress, R13 = No_Define::BaseAddress, R14 = No_Define::BaseAddress, R15 = No_Define::BaseAddress, RBP = 0, RSP = 0;
        RAX = client_info;
        RDI = No_Define::PEB; // mov rdi,gs:[rcx]
        // test rax,rax
        // je 00007FF75E7DD1CBh
        RCX = RDI;
        RCX = _rotr64(RCX, 0x13);
        RCX &= 0xF;
        // cmp rcx,0Eh
        // ja 00007FF75E7DCDF7h
        switch (RCX)
        {
        case 0: {
            RBX = No_Define::BaseAddress;
            R9 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = RDI;
            RCX = ~RCX;
            RCX -= RBX;
            RCX += 0xFFFFFFFFFFFFB03D;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x7;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0xE;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1C;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x38;
            RAX ^= RCX;
            RAX -= RBX;
            RCX = 0x17018B6945529074;
            RAX += RCX;
            RCX = 0xBC9C2D260721DFFD;
            RAX *= RCX;
            RAX += RBX;
            RCX = 0xA9FC06249DFE0873;
            RAX *= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= *(uint64_t*)(RCX + 0x5);
            return RAX;
        }
        case 1: {
            R11 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RBX = No_Define::BaseAddress;
            RDX = No_Define::BaseAddress + 0x290C;
            RCX = 0xAB38D0F7B94B733D;
            RAX *= RCX;
            R15 = 0xF4AD9C5147247AE8;
            RCX = RDI;
            RCX *= RDX;
            RCX -= RBX;
            RCX += R15;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x1D;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3A;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R11;
            RCX = ~RCX;
            RAX *= *(uint64_t*)(RCX + 0x5);
            RCX = 0x1202F95890F87C8;
            RAX -= RCX;
            return RAX;
        }
        case 2: {
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = RDI * 0xFE;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x22;
            RAX ^= RCX;
            RAX += RDI;
            RDX = 0x0;
            RCX = 0x432859FC2C7367E7;
            RAX *= RCX;
            RDX = _rotl64(RDX, 0x10);
            RCX = RAX;
            RDX ^= R10;
            RCX >>= 0x1B;
            RDX = ~RDX;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x36;
            RCX ^= RAX;
            RAX = *(uint64_t*)(RDX + 0x5);
            RAX *= RCX;
            RCX = 0x1CABBB23FD8D639B;
            RAX *= RCX;
            return RAX;
        }
        case 3: {
            RBX = No_Define::BaseAddress;
            R15 = No_Define::BaseAddress + 0x3483EDA1;
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            R11 = 0xE95C245BB2EE5516;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RCX = *(uint64_t*)(RCX + 0x5);
            RCX *= RAX;
            RAX = R15;
            RCX += RDI;
            RAX = ~RAX;
            RAX += R11;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x14;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x28;
            RAX ^= RCX;
            RAX -= RDI;
            RCX = 0x3555A17B83EFB3C7;
            RAX *= RCX;
            RCX = 0x160C6CDD5F954A38;
            RAX -= RDI;
            RAX -= RBX;
            RAX -= 0x2DF62A23;
            RAX ^= RCX;
            return RAX;
        }
        case 4: {
            R15 = No_Define::BaseAddress + 0xC7B6;
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RCX = RDI + RAX;
            RDX = ~RDX;
            RAX = *(uint64_t*)(RDX + 0x5);
            RAX *= RCX;
            RCX = 0x78D66A1CE27478D3;
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0xE;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1C;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x38;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1F;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3E;
            RAX ^= RCX;
            RCX = No_Define::BaseAddress + 0x6741;
            RCX = ~RCX;
            RCX += RAX;
            RAX = RDI + 1;
            RAX += RCX;
            RAX ^= RDI;
            RAX ^= R15;
            RCX = 0x24BCCA0B53388AEA;
            RAX ^= RCX;
            return RAX;
        }
        case 5: {
            RBX = No_Define::BaseAddress;
            RDX = No_Define::BaseAddress + 0x8569;
            R15 = No_Define::BaseAddress + 0xAA0B;
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = RDX;
            RCX = ~RCX;
            RCX ^= RDI;
            RAX -= RCX;
            RCX = 0x9B31E206C1CDD5C3;
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0xC;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x18;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x30;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= *(uint64_t*)(RCX + 0x5);
            RCX = 0xF51E2A85F29A70B;
            RAX -= RCX;
            RCX = 0x8989152276BB82D6;
            RAX ^= RCX;
            RAX -= RBX;
            RAX += 0xFFFFFFFFFFFF37F0;
            RAX += RDI;
            RAX ^= RDI;
            RAX ^= R15;
            return RAX;
        }
        case 6: {
            RBX = No_Define::BaseAddress;
            R9 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= *(uint64_t*)(RCX + 0x5);
            RCX = RBX + 0x2DB6EAAF;
            RCX += RDI;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x5;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0xA;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x14;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x28;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1A;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x34;
            RCX ^= RDI;
            RAX ^= RCX;
            RCX = 0x53575B3471D30C52;
            RAX ^= RCX;
            RCX = 0x83CC6E096B7D5731;
            RAX *= RCX;
            RCX = 0x2D268BD6FF3B4A65;
            RAX ^= RCX;
            return RAX;
        }
        case 7: {
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RBX = No_Define::BaseAddress;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R10;
            RCX = ~RCX;
            RAX *= *(uint64_t*)(RCX + 0x5);
            RCX = 0x1FE961BC0D596901;
            RAX += RCX;
            RAX ^= RBX;
            RCX = 0xEABC3B3886A0E103;
            RAX *= RCX;
            RAX += RBX;
            RDX = RDI;
            RDX = ~RDX;
            RCX = No_Define::BaseAddress + 0x7525;
            RDX += RCX;
            RCX = RAX;
            RAX = 0x37B2F642B57F479;
            RCX *= RAX;
            RAX = RDX;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            return RAX;
        }
        case 8: {
            RBX = No_Define::BaseAddress;
            R11 = No_Define::BaseAddress + 0x54BDDC6C;
            R9 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RAX -= RBX;
            RAX += 0xFFFFFFFFB0267D85;
            RAX += RDI;
            RCX = 0xDD7BD2E06188E77F;
            RAX ^= RCX;
            RCX = 0x76E83A4EECA680A9;
            RAX *= RCX;
            RCX = 0x6F616717865D112B;
            RAX += RCX;
            RCX = R11;
            RCX = ~RCX;
            RCX ^= RDI;
            RAX -= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= *(uint64_t*)(RCX + 0x5);
            RAX ^= RDI;
            RCX = RAX;
            RCX >>= 0x20;
            RAX ^= RCX;
            return RAX;
        }
        case 9: {
            uint64_t RSP_0x78 = No_Define::BaseAddress;
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = 0x4BBFA56727DC4AB9;
            RBX = No_Define::BaseAddress + 0x285FB43A;
            RSP_0x78 = RCX; // mov [rsp+78h],rcx
            RCX = RAX;
            RCX >>= 0xF;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            RAX *= RSP_0x78; // imul rax,[rsp+78h]
            RCX = RBX;
            RCX = ~RCX;
            RCX += RDI;
            RCX ^= RAX;
            RDX = 0x0;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RAX = *(uint64_t*)(RDX + 0x5);
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0x1B;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x36;
            RAX ^= RCX;
            RCX = 0x6EB4862326CD9433;
            RAX -= RCX;
            RCX = 0x2A7CA7719C633418;
            RAX ^= RCX;
            RAX += RDI;
            return RAX;
        }
        case 10: {
            R9 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = 0xEBB12D2C79FC5652;
            RAX ^= RCX;
            RCX = 0x9E6258824936A3C6;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RAX *= *(uint64_t*)(RCX + 0x5);
            RCX = RAX;
            RCX >>= 0x1D;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3A;
            RAX ^= RCX;
            RCX = 0x3D6B11E766286AA3;
            RAX *= RCX;
            RAX -= RDI;
            RCX = RAX;
            RCX >>= 0x7;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0xE;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1C;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x38;
            RAX ^= RCX;
            RAX -= RDI;
            return RAX;
        }
        case 11: {
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = RAX;
            RCX >>= 0x24;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x17;
            RAX ^= RCX;
            RCX = RAX;
            RDX = 0x0;
            RCX >>= 0x2E;
            RCX ^= RAX;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RAX = *(uint64_t*)(RDX + 0x5);
            RAX *= RCX;
            RCX = 0x5D5C607174CFC222;
            RAX -= RCX;
            RAX -= RDI;
            RCX = 0x1ACECF0113784AB7;
            RAX *= RCX;
            RAX += RDI;
            RCX = 0x7BD4F3E5AB768887;
            RAX *= RCX;
            return RAX;
        }
        case 12: {
            RBX = No_Define::BaseAddress;
            R15 = No_Define::BaseAddress + 0x6171;
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = RDI;
            RCX ^= R15;
            RAX += RCX;
            RAX ^= RBX;
            RDX = 0x0;
            RCX = RAX;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RAX = 0x673E272C0CA883CD;
            RCX ^= RAX;
            RDX = ~RDX;
            RAX = *(uint64_t*)(RDX + 0x5);
            RAX *= RCX;
            RCX = RDI;
            RCX = ~RCX;
            RAX += RCX;
            RAX -= RBX;
            RAX -= 0x191C62F6;
            RCX = RAX;
            RCX >>= 0x27;
            RAX ^= RCX;
            RCX = 0xE12F42EFE3D58BCB;
            RAX *= RCX;
            RCX = 0x285DF5F4C95F3162;
            RAX ^= RCX;
            return RAX;
        }
        case 13: {
            uint64_t RSP_0x78 = No_Define::BaseAddress;
            RCX = 0x5910987B2E4C2169;
            RBX = No_Define::BaseAddress;
            RSP_0x78 = RCX; // mov [rsp+78h],rcx
            R9 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RCX = *(uint64_t*)(RCX + 0x5);
            RCX *= RSP_0x78; // imul rcx,[rsp+78h]
            RAX *= RCX;
            RCX = 0xE2E24EFA6B663414;
            RAX ^= RCX;
            RAX -= RDI;
            RCX = No_Define::BaseAddress + 0x61F;
            RAX += RCX;
            RCX = RAX;
            RCX >>= 0x27;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x4;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x8;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x10;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x20;
            RAX ^= RCX;
            RCX = RBX + 0x14CAB09B;
            RCX += RDI;
            RAX -= RBX;
            RAX ^= RCX;
            return RAX;
        }
        case 14: {
            uint64_t RSP_0x70 = No_Define::BaseAddress;
            RCX = 0xC2A87682DDC9E25D;
            RSP_0x70 = RCX; // mov [rsp+70h],rcx
            R9 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RCX = RAX;
            RCX >>= 0xF;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x1E;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x3C;
            RAX ^= RCX;
            RAX ^= RDI;
            RCX = RAX;
            RCX >>= 0x1;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x2;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x4;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x8;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x10;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x20;
            RAX ^= RCX;
            RCX = 0x8ADDB5A6833CD70C;
            RAX += RCX;
            RCX = 0x71785D8AD6471764;
            RAX ^= RCX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= R9;
            RCX = ~RCX;
            RCX = *(uint64_t*)(RCX + 0x5);
            RCX *= RSP_0x70; // imul rcx,[rsp+70h]
            RAX *= RCX;
            RCX = RAX;
            RCX >>= 0x21;
            RAX ^= RCX;
            return RAX;
        }
        case 15: {
            RBX = No_Define::BaseAddress;
            R13 = 0x3C85E73829FCC7AD;
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D912F);
            RAX *= R13;
            RCX = 0xE37E90332B6845B6;
            RAX ^= RCX;
            RCX = RAX;
            RCX >>= 0x24;
            RAX ^= RCX;
            RAX += RBX;
            RAX ^= RDI;
            RAX += RBX;
            RCX = RAX;
            RDX = 0x0;
            RCX >>= 0x28;
            RCX ^= RAX;
            RDX = _rotl64(RDX, 0x10);
            RDX ^= R10;
            RDX = ~RDX;
            RAX = *(uint64_t*)(RDX + 0x5);
            RAX *= RCX;
            return RAX;
        }
        }
    }
    uint64_t DecryptBoneBase()
    {
        uint64_t RAX = No_Define::BaseAddress, RBX = No_Define::BaseAddress, RCX = No_Define::BaseAddress, RDX = No_Define::BaseAddress, R8 = No_Define::BaseAddress, RDI = No_Define::BaseAddress, RSI = No_Define::BaseAddress, R9 = No_Define::BaseAddress, R10 = No_Define::BaseAddress, R11 = No_Define::BaseAddress, R12 = No_Define::BaseAddress, R13 = No_Define::BaseAddress, R14 = No_Define::BaseAddress, R15 = No_Define::BaseAddress, RBP = 0, RSP = 0;
        RDX = *(uint64_t*)(No_Define::BaseAddress + 0x15E18A18);
        if (RDX == 0)
        {
            return 0;
        }
        R8 = No_Define::PEB; // mov r8,gs:[rax]
        R8 = ~R8;
        // test rdx,rdx
        // je 00007FF75EB0D365h
        RAX = R8;
        RAX = _rotl64(RAX, 0x26);
        RAX &= 0xF;
        // cmp rax,0Eh
        // ja 00007FF75EB0CEE7h
        switch (RAX)
        {
        case 0: {
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            R14 = No_Define::BaseAddress + 0x676D94A3;
            RAX = RDX;
            RAX >>= 0x3;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x6;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0xC;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x18;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x30;
            RDX ^= RAX;
            RAX = 0xD635FD6F5740DF17;
            RDX *= RAX;
            RAX = R8;
            RAX *= R14;
            RDX += RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RAX = No_Define::BaseAddress + 0x3496E896;
            R13 = 0x891801D00A4665B;
            RAX = ~RAX;
            RAX -= R8;
            RAX += R13;
            RDX += RAX;
            RAX = No_Define::BaseAddress;
            RDX ^= RAX;
            RAX = 0x3059E19BF5C898E5;
            RDX *= RAX;
            return RDX;
        }
        case 1: {
            // pushfq
            // push rdx
            // pop rdx
            // pop rdx
            R12 = No_Define::BaseAddress + 0x74050ED8;
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = R12;
            RAX -= R8;
            RDX += RAX;
            RDX -= R8;
            RDX ^= R8;
            RAX = 0x5BB3382495788FD9;
            RDX *= RAX;
            RCX = 0x0;
            RAX = 0x5B9DDF9B7BC38403;
            RCX = _rotl64(RCX, 0x10);
            RAX += RDX;
            RCX ^= RBX;
            RCX = _byteswap_uint64(RCX);
            RDX = *(uint64_t*)(RCX + 0xB);
            RDX *= RAX;
            RAX = RDX;
            RAX >>= 0x20;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x11;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x22;
            RDX ^= RAX;
            return RDX;
        }
        case 2: {
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = RDX;
            RAX >>= 0x12;
            RDX ^= RAX;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RAX = RDX;
            RCX ^= RBX;
            RAX >>= 0x24;
            RAX ^= RDX;
            RCX = _byteswap_uint64(RCX);
            RDX = *(uint64_t*)(RCX + 0xB);
            RDX *= RAX;
            RCX = R8;
            RCX = ~RCX;
            RAX = No_Define::BaseAddress + 0x8D63;
            RDX += RAX;
            RDX += RCX;
            RAX = 0xFF36F9B289267D23;
            RDX *= RAX;
            RAX = RDX;
            RAX >>= 0x26;
            RDX ^= RAX;
            RDX ^= R8;
            RAX = 0x1FC63BF66339890F;
            RDX *= RAX;
            return RDX;
        }
        case 3: {
            // pushfq
            // push rdx
            // pop rdx
            // pop rdx
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RDX += R8;
            RAX = RDX;
            RAX >>= 0xF;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x1E;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x3C;
            RDX ^= RAX;
            RAX = 0x3437489FC93631C1;
            RDX += RAX;
            RAX = RDX;
            RAX >>= 0x5;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0xA;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x14;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x28;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x3;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x6;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0xC;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x18;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x30;
            RDX ^= RAX;
            RDX -= R8;
            RCX = 0x0;
            RCX = _rotl64(RCX, 0x10);
            RCX ^= RBX;
            RAX = No_Define::BaseAddress;
            RDX -= RAX;
            RAX = 0xFDF3D74B7A69C45B;
            RAX *= RDX;
            RDX = 0x52547ABD86BE0CB4;
            RAX += RDX;
            RCX = _byteswap_uint64(RCX);
            RDX = *(uint64_t*)(RCX + 0xB);
            RDX *= RAX;
            return RDX;
        }
        case 4: {
            uint64_t RBP_0x48 = No_Define::BaseAddress;
            uint64_t RSP_0x48 = No_Define::BaseAddress;
            uint64_t RSP_0x78 = No_Define::BaseAddress;
            // pushfq
            // push rcx
            // pop rcx
            // pop rcx
            // popfq
            RAX = No_Define::BaseAddress + 0x6D8B;
            RSP_0x48 = RAX; // mov [rsp+48h],rax
            RAX = 0xA6572F476EA14F7B;
            RSP_0x78 = RAX; // mov [rsp+78h],rax
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = R8;
            RAX -= RBP_0x48; // sub rax,[rbp+48h]
            RAX -= 0x4929CCC0;
            RDX ^= RAX;
            RAX = R8;
            RAX = ~RAX;
            RAX += RSP_0x48; // add rax,[rsp+48h]
            RDX ^= RAX;
            RAX = 0x46B53CB403B92895;
            RDX += RAX;
            RAX = 0xCCE222429417FA02;
            RDX ^= RAX;
            RAX = No_Define::BaseAddress;
            RDX -= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= RBX;
            RAX = _byteswap_uint64(RAX);
            RAX = *(uint64_t*)(RAX + 0xB);
            RAX *= RSP_0x78; // imul rax,[rsp+78h]
            RDX *= RAX;
            RAX = RDX;
            RAX >>= 0xF;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x1E;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x3C;
            RDX ^= RAX;
            return RDX;
        }
        case 5: {
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            R15 = No_Define::BaseAddress + 0xC902;
            RAX = R8;
            RAX *= R15;
            RDX -= RAX;
            RAX = RDX;
            RAX >>= 0x12;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x24;
            RDX ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= RBX;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RAX = 0x7887CB49CAD27C83;
            RDX *= RAX;
            RAX = No_Define::BaseAddress;
            RAX += 0x5DBA;
            RAX += R8;
            RDX += RAX;
            RAX = RDX;
            RAX >>= 0xC;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x18;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x30;
            RDX ^= RAX;
            RAX = No_Define::BaseAddress + 0xD9F3;
            RDX -= R8;
            RDX += RAX;
            RAX = RDX;
            RAX >>= 0x8;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x10;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x20;
            RDX ^= RAX;
            return RDX;
        }
        case 6: {
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            R12 = No_Define::BaseAddress + 0x56AD1EF7;
            RCX = 0x0;
            RAX = RDX;
            RCX = _rotl64(RCX, 0x10);
            RAX >>= 0x26;
            RCX ^= RBX;
            RAX ^= RDX;
            RCX = _byteswap_uint64(RCX);
            RDX = *(uint64_t*)(RCX + 0xB);
            RDX *= RAX;
            RAX = RDX;
            RAX >>= 0x14;
            RDX ^= RAX;
            RCX = RDX;
            RCX >>= 0x28;
            RAX = 0x73E3C1626886AD89;
            RCX ^= RDX;
            RDX = R8;
            RDX *= R12;
            RDX += RCX;
            RDX *= RAX;
            RDX -= R8;
            RAX = No_Define::BaseAddress;
            RDX ^= RAX;
            RAX = 0x5BE12EB58C328E79;
            RDX += RAX;
            return RDX;
        }
        case 7: {
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RCX = R8 - 0x6B958332;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= RBX;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RAX = No_Define::BaseAddress;
            RDX ^= RAX;
            RDX -= RAX;
            RCX += RDX;
            RAX = RCX;
            RAX >>= 0xC;
            RCX ^= RAX;
            RAX = RCX;
            RAX >>= 0x18;
            RCX ^= RAX;
            RDX = RCX;
            RDX >>= 0x30;
            RAX = 0xA2777C64321A6CF;
            RDX ^= RCX;
            RDX *= RAX;
            RAX = 0x3D998F50D02DE848;
            RDX -= RAX;
            RDX ^= R8;
            RAX = 0x44777CC2F2CDCF18;
            RDX ^= RAX;
            return RDX;
        }
        case 8: {
            uint64_t RBP_0x48 = No_Define::BaseAddress;
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            R12 = No_Define::BaseAddress + 0xC270;
            RCX = R8;
            RAX = R12;
            RAX = ~RAX;
            RCX = ~RCX;
            RCX += RAX;
            RDX ^= RCX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= RBX;
            RAX = _byteswap_uint64(RAX);
            RAX = *(uint64_t*)(RAX + 0xB);
            RDX *= RAX;
            RAX = 0x9F3A04B73F91D7BF;
            RDX *= RAX;
            RAX = 0x4B4AF50AA7AE5554;
            RDX += RAX;
            RAX = 0x28274EB8C143F7E5;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x15;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x2A;
            RDX ^= RAX;
            RAX = R8;
            RAX -= RBP_0x48; // sub rax,[rbp+48h]
            RAX += 0xFFFFFFFFFFFF0C01;
            RDX += RAX;
            RAX = No_Define::BaseAddress + 0x6F41;
            RAX = ~RAX;
            RAX++;
            RAX += R8;
            RDX += RAX;
            return RDX;
        }
        case 9: {
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RDX += R8;
            RAX = No_Define::BaseAddress;
            RAX += 0x11B6;
            RAX += R8;
            RDX ^= RAX;
            RAX = No_Define::BaseAddress;
            RDX -= RAX;
            RAX = RDX;
            RAX >>= 0x5;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0xA;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x14;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x28;
            RDX ^= RAX;
            RAX = 0x3E29187B34B94B2B;
            RDX *= RAX;
            RAX = 0x2FF261694EB43A81;
            RDX += RAX;
            RAX = 0x431D1D596FDAE99B;
            RDX *= RAX;
            return RDX;
        }
        case 10: {
            R14 = No_Define::BaseAddress + 0x1DD8;
            R15 = No_Define::BaseAddress + 0x53356CF1;
            R10 = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = R8;
            RAX = ~RAX;
            RAX ^= R14;
            RDX -= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R10;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RAX = 0x9251D28D0725F547;
            RDX *= RAX;
            RAX = R8;
            RAX = ~RAX;
            RDX ^= RAX;
            RDX ^= R15;
            RAX = 0xB570D6A46CA6BDA;
            RDX -= RAX;
            RAX = RDX;
            RAX >>= 0x11;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x22;
            RDX ^= RAX;
            RAX = 0xF541FBA8EA6DB70D;
            RDX *= RAX;
            RAX = No_Define::BaseAddress;
            RDX -= RAX;
            return RDX;
        }
        case 11: {
            uint64_t RSP_0x48 = No_Define::BaseAddress;
            // pushfq
            // push rbx
            // pop rbx
            // pop rbx
            // popfq
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = No_Define::BaseAddress + 0x4D63C65D;
            RSP_0x48 = RAX; // mov [rsp+48h],rax
            R12 = No_Define::BaseAddress + 0x7A87E289;
            RAX = R8;
            RAX = ~RAX;
            RAX += RSP_0x48; // add rax,[rsp+48h]
            RDX ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= RBX;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RAX = RDX;
            RAX >>= 0x1F;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x3E;
            RDX ^= RAX;
            RAX = 0x4386482E23BD7BAB;
            RDX *= RAX;
            RAX = R8;
            RAX = ~RAX;
            RAX += R12;
            RDX ^= RAX;
            RAX = No_Define::BaseAddress;
            RAX += 0x5D6A5202;
            RAX += R8;
            RDX += RAX;
            RAX = 0x5D0357B59D909B8;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x25;
            RDX ^= RAX;
            return RDX;
        }
        case 12: {
            uint64_t RBP_0x48 = No_Define::BaseAddress;
            // pushfq
            // push rdx
            // pop rdx
            // pop rdx
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = RDX;
            RAX >>= 0x14;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x28;
            RDX ^= RAX;
            RAX = R8;
            RAX -= RBP_0x48; // sub rax,[rbp+48h]
            RAX += 0xFFFFFFFFB8A79E69;
            RDX += RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= RBX;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RDX -= R8;
            RAX = RDX;
            RAX >>= 0x27;
            RDX ^= RAX;
            RDX += R8;
            RAX = 0xDC42F705062C7C2B;
            RDX *= RAX;
            RAX = 0x22D95990904EF823;
            RDX += RAX;
            return RDX;
        }
        case 13: {
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            R15 = No_Define::BaseAddress + 0x4C7B;
            RAX = 0x8083BF913D676785;
            RDX *= RAX;
            RAX = R15;
            RAX = ~RAX;
            RAX *= R8;
            RDX += RAX;
            RAX = RDX;
            RAX >>= 0x1C;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x38;
            RDX ^= RAX;
            RDX -= R8;
            RAX = No_Define::BaseAddress;
            RDX -= RAX;
            RAX = 0xA2C3AADF199E32E1;
            RDX *= RAX;
            RAX = 0x23580E1270B613C4;
            RDX += RAX;
            RAX = RDX;
            RAX >>= 0xF;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x1E;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x3C;
            RDX ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= RBX;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RAX = RDX;
            RAX >>= 0x1F;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x3E;
            RDX ^= RAX;
            return RDX;
        }
        case 14: {
            R9 = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = No_Define::BaseAddress;
            RDX ^= RAX;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= R9;
            RAX = _byteswap_uint64(RAX);
            RDX *= *(uint64_t*)(RAX + 0xB);
            RAX = RDX;
            RAX >>= 0x14;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x28;
            RDX ^= RAX;
            RAX = 0x44A70ED11D0E61A3;
            RDX -= RAX;
            RAX = 0x212713CA8BC0FC71;
            RDX *= RAX;
            RAX = 0x7B0A0E68889C8F78;
            RDX += RAX;
            return RDX;
        }
        case 15: {
            uint64_t RSP_0x48 = No_Define::BaseAddress;
            // pop rax
            // pop rax
            // popfq
            RBX = *(uint64_t*)(No_Define::BaseAddress + 0x71D924F);
            RAX = 0x76F87EA0A47CB0AD;
            RSP_0x48 = RAX; // mov [rsp+48h],rax
            RAX = No_Define::BaseAddress;
            RDX += RAX;
            RDX ^= R8;
            RAX = 0x0;
            RAX = _rotl64(RAX, 0x10);
            RAX ^= RBX;
            RAX = _byteswap_uint64(RAX);
            RAX = *(uint64_t*)(RAX + 0xB);
            RAX *= RSP_0x48; // imul rax,[rsp+48h]
            RDX *= RAX;
            RAX = RDX;
            RAX >>= 0x11;
            RDX ^= RAX;
            RAX = RDX;
            RAX >>= 0x22;
            RDX ^= RAX;
            RAX = 0x660C3C0933677E41;
            RDX += RAX;
            RAX = No_Define::BaseAddress;
            RDX ^= RAX;
            RAX = 0xF87C74347306E12C;
            RDX ^= RAX;
            return RDX;
        }
        }
    }
    uint64_t DecryptBoneIndex(uint64_t base, uint32_t index)
    {
        uint64_t RAX = No_Define::BaseAddress, RBX = No_Define::BaseAddress, RCX = No_Define::BaseAddress, RDX = No_Define::BaseAddress, R8 = No_Define::BaseAddress, RDI = No_Define::BaseAddress, RSI = No_Define::BaseAddress, R9 = No_Define::BaseAddress, R10 = No_Define::BaseAddress, R11 = No_Define::BaseAddress, R12 = No_Define::BaseAddress, R13 = No_Define::BaseAddress, R14 = No_Define::BaseAddress, R15 = No_Define::BaseAddress, RBP = 0, RSP = 0;
        RBX = index;
        RCX = RBX * 0x13C8;
        RAX = 0x1DB46762E3D52EF7;
        RBX = No_Define::BaseAddress;
        RAX = _umul128(RAX, RCX, &RDX);
        R10 = 0x86C2D6724C0021B1;
        RDX >>= 0xA;
        RAX = RDX * 0x2279;
        RCX -= RAX;
        RAX = 0x342C53A914269ED;
        R8 = RCX * 0x2279;
        RAX = _umul128(RAX, R8, &RDX);
        RDX >>= 0x7;
        RAX = RDX * 0x2741;
        R8 -= RAX;
        RAX = 0x5197F7D73404147;
        RAX = _umul128(RAX, R8, &RDX);
        RAX = R8;
        RAX -= RDX;
        RAX >>= 0x1;
        RAX += RDX;
        RAX >>= 0x8;
        RCX = RAX * 0x1F6;
        RAX = 0x47AE147AE147AE15;
        RAX = _umul128(RAX, R8, &RDX);
        RAX = R8;
        RAX -= RDX;
        RAX >>= 0x1;
        RAX += RDX;
        RAX >>= 0x4;
        RCX += RAX;
        RAX = RCX * 0x32;
        RCX = R8 * 0x34;
        RCX -= RAX;
        RAX = *(uint16_t*)(RCX + RBX + 0x71EC670);
        R8 = RAX * 0x13C8;
        RAX = R10;
        RAX = _umul128(RAX, R8, &RDX);
        RAX = R10;
        RDX >>= 0xC;
        RCX = RDX * 0x1E65;
        R8 -= RCX;
        R9 = R8 * 0x2742;
        RAX = _umul128(RAX, R9, &RDX);
        RDX >>= 0xC;
        RAX = RDX * 0x1E65;
        R9 -= RAX;
        RAX = 0x90FDBC090FDBC091;
        RAX = _umul128(RAX, R9, &RDX);
        RAX = 0x29E4129E4129E413;
        RDX >>= 0x7;
        RCX = RDX * 0xE2;
        RAX = _umul128(RAX, R9, &RDX);
        RAX = R9;
        RAX -= RDX;
        RAX >>= 0x1;
        RAX += RDX;
        RAX >>= 0x5;
        RCX += RAX;
        RAX = RCX * 0x6E;
        RCX = R9 * 0x70;
        RCX -= RAX;
        RSI = *(uint16_t*)(RCX + RBX + 0x71F2880);
        return RSI;
    }
    auto DecryptRef_Def(refdefKeyStruct crypt) -> uint64_t
    {
        uint64_t baseAddr = No_Define::BaseAddress;
        DWORD lower = crypt.ref0 ^ (crypt.ref2 ^ (uint64_t)(baseAddr + offsets::Ref_Def)) * ((crypt.ref2 ^ (uint64_t)(baseAddr + offsets::Ref_Def)) + 2);
        DWORD upper = crypt.ref1 ^ (crypt.ref2 ^ (uint64_t)(baseAddr + offsets::Ref_Def + 0x4)) * ((crypt.ref2 ^ (uint64_t)(baseAddr + offsets::Ref_Def + 0x4)) + 2);
        return (uint64_t)upper << 32 | lower; // Merge Both DWORD into QWORD
    }
    Vector3 GetBonePosition(uint64_t BoneIndexDecryption, int BoneNumber)
    {
        auto BonePtrIndex = BoneIndexDecryption;
        auto bonePtr = *(uint64_t*)(Addresses::BONE_BASE + (BonePtrIndex * offsets::bones::size) + 0xC0);
        if (bonePtr)
        {
            auto bonePos = *(Vector3*)(bonePtr + (BoneNumber * 0x20) + 0x10);
            if (bonePos.x != 0 || bonePos.y != 0 || bonePos.z != 0)
            {
                auto basePos = *(Vector3*)(Addresses::INFO + offsets::bones::bone_base);//48 05 ? ? ? ? 48 89 44 24 ? 4C 8D 84 24 ? ? ? ? 
                bonePos.x += basePos.x;
                bonePos.y += basePos.y;
                bonePos.z += basePos.z;
                return bonePos;
            }
            return bonePos;
        }
        return Vector3{};
    }
}

uint64_t GetRefDef()
{
    auto encRef_Def = *(refdefKeyStruct*)(No_Define::BaseAddress + offsets::Ref_Def);
    return decryption::DecryptRef_Def(encRef_Def);
}
uint64_t GetClientInfo() {
    auto encinfo = *(uint64_t*)(No_Define::BaseAddress + offsets::CLIENT_INFO);
    return decryption::DecryptClientInfo(encinfo);
}
uint64_t GetClientBase(uint64_t client_info) {
    auto encbase = *(uint64_t*)(client_info + offsets::CLIENT_BASE);
    return decryption::DecryptClientBase(encbase);
}
uint64_t GetNameList() {
    auto ptr = *(uint64_t*)(No_Define::BaseAddress + offsets::Name_Array);
    return ptr + offsets::Name_Array_Padding;
}
uint64_t GetVisibleBase(uint64_t imageBase)
{
    for (int32_t j = 4000; j >= 0; --j)
    {
        uint64_t n_index = (j + (j << 2)) << 0x6;
        uint64_t vis_base = *(uint64_t*)(imageBase + offsets::Bones_Distribute);

        if (!vis_base)
            continue;

        uint64_t vis_base_ptr = vis_base + n_index;
        uint64_t cmp_function = *(uint64_t*)(vis_base_ptr + 0x90);

        if (!cmp_function)
            continue;

        uint64_t about_visible = imageBase + offsets::Bones_Visible;
        if (cmp_function == about_visible)
        {
            return vis_base_ptr;
        }
    }
    return NULL;
}