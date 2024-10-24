#pragma once

#include <imgui.h>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include "utils.h"

class ECL_File;
class ECL_Sub;
class ECL_Ins;

enum InsArgType
{
	A_FLOAT, A_INT, SUBNAME_STR, SPELL_STR, SUB_PASS_ARG, OFFSET
};

struct InsArg
{
	InsArgType type;
	bool is_stack;

	std::u8string spellstr_u8;
	union
	{
		float float_arg;
		int32_t int_arg;
		int32_t ofs_arg;
		struct{
			int32_t subname_size;
			const char* subname_arg;
		};
		struct {
			int32_t spellstr_size;
			const char* spellstr_arg;
		};
		struct {
			char pass_type;
			char rcv_type;
			union {
				int32_t passed_iarg;
				float passed_farg;
			} passed_val;
		} sub_pass_arg;
	};
	void SetFloat(float f) { type = InsArgType::A_FLOAT; float_arg = f; }
	void SetInt(int32_t i) { type = InsArgType::A_INT; int_arg=i; }
	void SetOffset(int32_t o) { type = InsArgType::OFFSET; ofs_arg = o; }

	void SetSubNameStr(int32_t sz, const char* name) { type = InsArgType::SUBNAME_STR; subname_arg = name; subname_size = sz; }
	void SetSpellStr(int32_t sz, const char* spellstr) { type = InsArgType::SPELL_STR; spellstr_arg = spellstr; spellstr_size = sz; spellstr_u8 = str2u8(GetSpellStr().c_str(), 932); }
		//https://learn.microsoft.com/zh-cn/windows/win32/Intl/code-page-identifiers
		//jis=932
	void SetSubPassArgInt(char rcv, int32_t t) {
		type = InsArgType::SUB_PASS_ARG; sub_pass_arg.pass_type = 'i'; sub_pass_arg.rcv_type = rcv; sub_pass_arg.passed_val.passed_iarg = t;
	}
	void SetSubPassArgFloat(char rcv, float t) {
		type = InsArgType::SUB_PASS_ARG; sub_pass_arg.pass_type = 'f'; sub_pass_arg.rcv_type = rcv; sub_pass_arg.passed_val.passed_farg = t;
	}
	std::string GetSpellStr();
};
std::ostream& operator<<(std::ostream& os, InsArg& arg);

struct ECL_DataHeader
{
	char sig[4];
	uint16_t unknown_one;
	uint16_t include_len;
	uint32_t include_ofs;
	uint32_t unknown_zero1;
	uint32_t sub_count;
	uint32_t zeros_pad[4];
};

struct ECL_IncludeHeader
{
	char sig[4];
	uint32_t num_files;
};


struct ECL_SubHeader
{
	char sig[4];
	int32_t data_ofs;
	int32_t zeros[2];
};

struct ECL_InsHeader
{
	int32_t time;
	int16_t code;
	int16_t size;
	int16_t stack_mask;
	int8_t diff_mask;
	int8_t arg_count;
	int32_t stack_count;
};

class ECL_Include
{
public:
	ECL_IncludeHeader mHeader;
	std::vector<std::string> mIncludeFiles;
public:
	friend std::istream& operator>>(std::istream& is, ECL_Include& ecl_file);
	void Clear() { memset(&mHeader, 0, sizeof(mHeader)); mIncludeFiles.clear(); }
};
std::istream& operator>>(std::istream& is, ECL_Include& ecl_include);

class ECL_Ins
{
public:
	ECL_InsHeader mHeader;
	std::vector<int32_t> mArgs;

	bool has_dumped = false;
	std::vector<InsArg> mArgsDumped;
	int32_t mOfs;
	int32_t mIndex;
	int32_t mSubIndex;
	std::string mInsHex;

	int32_t mView_Index;
public:
	std::string& GetInsHex();
	std::vector<InsArg>& GetInsArgs(int version);
	ECL_Ins(int32_t ofs = -1, int32_t index = -1, int32_t subIndex = -1) :mOfs(ofs), mIndex(index), mSubIndex(subIndex) {};
	friend std::istream& operator>>(std::istream& is, ECL_Ins& ecl_ins);
	friend std::ostream& operator<<(std::ostream& os, ECL_Ins& ecl_ins);
	friend class ECL_Sub;
	friend class ECL_File;
	void Clear() { memset(&mHeader, 0, sizeof(mHeader)); mArgs.clear(); has_dumped = false; mArgsDumped.clear(); mOfs = 0; mIndex = 0; mSubIndex = 0; mInsHex = ""; }
};
std::istream& operator>>(std::istream& is, ECL_Ins& ecl_ins);
std::ostream& operator<<(std::ostream& os, ECL_Ins& ecl_ins);


class ECL_Sub
{
public:
	ECL_SubHeader mHeader;
	std::vector<ECL_Ins> mInses;

	int32_t mOfs;
	int32_t mIndex;
	std::string mName;

	int32_t mView_Index;
public:
	ECL_Sub(int32_t ofs = -1, int32_t index = -1, std::string name = "") :mOfs(ofs), mIndex(index), mName(name) {};
	friend std::istream& operator>>(std::istream& is, ECL_Sub& ecl_sub);
	friend class ECL_File;
	void Clear() { memset(&mHeader, 0, sizeof(mHeader)); mInses.clear(); mOfs = 0; mIndex = 0; mName = ""; }
};
std::istream& operator>>(std::istream& is, ECL_Sub& ecl_sub);


class ECL_File
{
public:
	int32_t version;

	ECL_DataHeader mHeader;
	ECL_Include mAnmInclude;
	ECL_Include mEclInclude;
	std::vector<int32_t> mSubPtrs;
	std::vector<std::string> mSubNames;
	std::vector<ECL_Sub> mSubs;

public:
	friend std::istream& operator>>(std::istream& is, ECL_File& ecl_file);
	void GetInsList(std::vector<ECL_Ins>& out_inses);
	int CalcSubIndexAt(int32_t address);
	void Clear() { version = 0; memset(&mHeader, 0, sizeof(mHeader)); mAnmInclude.Clear(); mEclInclude.Clear(); mSubPtrs.clear(); mSubNames.clear(); mSubs.clear(); }
};
std::istream& operator>>(std::istream& is, ECL_File& ecl_file);