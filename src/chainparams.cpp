// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2013-2014 The Vaperscoin developers
// Copyright (c)      2014 The Inutoshi developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
 //   0xf58aa16c,
//    0xa80dfb94, 0xf1a134d0, 0x4215042e, 0x7c51486d, 0x3a51486d, 0xd5c63832, 0xde5b7e02, 0xdb176018,
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc0;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xc0;
        vAlertPubKey = ParseHex("04d4da7a5dae4db797d9b0644d57a5cd50e05a70f36091cd62e2fc41c98ded06340be5a43a35e185690cd9cde5d72da8f6d065b499b06f51dcfba14aad859f443a");
        nDefaultPort = 4444;
        nRPCPort = 4455;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 2850000;


        
        
        
        
        
        
        const char* pszTimestamp = "The time we all stop to smoke,a Monday in 01/2017";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 7500 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1463936140;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 7712224;

//if (true && genesis.GetHash() != hashGenesisBlock)
//        {
//            printf("Searching for genesis block...\n");
//            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
//            uint256 thash;
//            char scratchpad[SCRYPT_SCRATCHPAD_SIZE];
//
//            while (true)
//            {
//                scrypt_1024_1_1_256_sp(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
//                if (thash <= hashTarget)
//                    break;
//                if ((genesis.nNonce & 0xFFF) == 0)
//                {
//                    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
//                }
//                ++genesis.nNonce;
//                if (genesis.nNonce == 0)
//                {
//                    printf("NONCE WRAPPED, incrementing time\n");
//                    ++genesis.nTime;
//                }
//            }
//            printf("genesis.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
//            printf("genesis.nTime = %u \n", genesis.nTime);
//            printf("genesis.nNonce = %u \n", genesis.nNonce);
//            
//            }

 // If genesis block hash does not match, then generate new genesis hash.
        if (false && genesis.GetHash() != hashGenesisBlock)
	      {
           printf("Searching for genesis block...\n");
            // This will figure out a valid hash and Nonce if you're
            // creating a different genesis block:
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;
            char scratchpad[SCRYPT_SCRATCHPAD_SIZE];

//            loop

			while (true)
            {
#if defined(USE_SSE2)
                // Detection would work, but in cases where we KNOW it always has SSE2,
                // it is faster to use directly than to use a function pointer or conditional.
#if defined(_M_X64) || defined(__x86_64__) || defined(_M_AMD64) || (defined(MAC_OSX) && defined(__i386__))
                // Always SSE2: x86_64 or Intel MacOS X
                scrypt_1024_1_1_256_sp_sse2(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
#else
                // Detect SSE2: 32bit x86 Linux or Windows
                scrypt_1024_1_1_256_sp(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
#endif
#else
                // Generic scrypt
                scrypt_1024_1_1_256_sp_generic(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
#endif
                if (thash <= hashTarget)
                    break;
               if ((genesis.nNonce & 0xFFF) == 0)
                {
                    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                }
               ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            printf("genesis.nTime = %u \n", genesis.nTime);
            printf("genesis.nNonce = %u \n", genesis.nNonce);
            printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //idk
        }








        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xfc223fac4c3a51e41003d7a4d9aa8054f65a29b3120d5d2b48b27f67aac2b0f3"));
        assert(genesis.hashMerkleRoot == uint256("0xe5c810d6abbbd2d14e439442bd9e006454692ae1e5c6d5372c1f86a4dbce56f7"));

        vSeeds.push_back(CDNSSeedData("37.187.125.97", "37.187.125.97"));
//        vSeeds.push_back(CDNSSeedData("mophides.com", "seed.mophides.com"));
//        vSeeds.push_back(CDNSSeedData("dglibrary.org", "seed.dglibrary.org"));
//        vSeeds.push_back(CDNSSeedData("epcchain.info", "seed.epcchain.info"));

        // Workaround for Boost not being quite compatible with C++11;
        std::vector<unsigned char> pka = list_of(70);
        base58Prefixes[PUBKEY_ADDRESS] = pka;
        
        std::vector<unsigned char> sca = list_of(22);
        base58Prefixes[SCRIPT_ADDRESS] = sca;
        
        std::vector<unsigned char> sk  = list_of(198);
        base58Prefixes[SECRET_KEY]     = sk;
        
        std::vector<unsigned char> epk = list_of(0x04)(0x88)(0xC4)(0x2E);
        base58Prefixes[EXT_PUBLIC_KEY] = epk;
        
        std::vector<unsigned char> esk = list_of(0x04)(0x88)(0xE1)(0xF4);
        base58Prefixes[EXT_SECRET_KEY] = esk;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const uint64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        vAlertPubKey = ParseHex("042756726da3c7ef515d89212ee1705023d14be389e25fe15611585661b9a20021908b2b80a3c7200a0139dd2b26946606aab0eef9aa7689a6dc2c7eee237fa834");
        nDefaultPort = 14444;
        nRPCPort = 14455;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1391503289;
        genesis.nNonce = 997879;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x8753b01bc2dafef2973a1378eb9465617893da73ac177e5ed376f05f42c2a820"));

        vFixedSeeds.clear();
        vSeeds.clear();
//        vSeeds.push_back(CDNSSeedData("testepc.lionservers.de", "testepc-seed.lionservers.de"));
//        vSeeds.push_back(CDNSSeedData("lionservers.de", "testepc-seed-static.lionservers.de"));

        // Boost sucks, and should not be used. Workaround for Boost not being compatible with C++11;
        
        std::vector<unsigned char> pka = list_of(113);
        base58Prefixes[PUBKEY_ADDRESS] = pka;
        std::vector<unsigned char> sca = list_of(196);
        base58Prefixes[SCRIPT_ADDRESS] = sca;
        std::vector<unsigned char> sk  = list_of(241);
        base58Prefixes[SECRET_KEY]     = sk;
        std::vector<unsigned char> epk = list_of(0x04)(0x35)(0xD1)(0xDF);
        base58Prefixes[EXT_PUBLIC_KEY] = epk;
        std::vector<unsigned char> esk = list_of(0x04)(0x35)(0x75)(0xA4);
        base58Prefixes[EXT_SECRET_KEY] = esk;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x3d2160a3b5dc4a9d62e7e66a295f70313ac808440ef7400d6c0772171ce973a5"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual bool SimplifiedRewards() const { return true; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}