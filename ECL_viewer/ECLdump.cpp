#include "ECLdump.h"
#include "ECLmap.h"
#include "utils.h"
#include <format>
int GetPadN(int cur_sz, int n)
{
	if (cur_sz % n == 0)
		return 0;
	return n - cur_sz%n;
}

std::ostream& operator<<(std::ostream& os, InsArg& arg)
{
	if(!arg.is_stack)
		switch (arg.type)
		{
		default:
		case InsArgType::A_INT:
			os << arg.int_arg; break;
		case InsArgType::A_FLOAT:
			os << arg.float_arg<<"f"; break;
		case InsArgType::SUBNAME_STR:
			os << "\"" << arg.subname_arg << "\""; break;
		case InsArgType::SPELL_STR:
			os <<"\"" << (char*)arg.spellstr_u8.c_str() <<"\""; break;
		case InsArgType::OFFSET:
			os << arg.ofs_arg; break;
		case InsArgType::SUB_PASS_ARG:
			if (arg.sub_pass_arg.pass_type=='i'){
				if (arg.sub_pass_arg.rcv_type == 'f')
					os << "(float)";
				os << arg.sub_pass_arg.passed_val.passed_iarg;
			}else{
				if (arg.sub_pass_arg.rcv_type == 'i')
					os << "(int)";
				os << arg.sub_pass_arg.passed_val.passed_farg;
			}
			break;
		}
	else
		switch (arg.type){
		default:
		case InsArgType::A_INT:
			os <<"[" << arg.int_arg<<"]"; break;
		case InsArgType::A_FLOAT:
			os << "[" << arg.float_arg << "f]"; break;
		case InsArgType::SUBNAME_STR:
			os << "\"" << arg.subname_arg << "\""; break;
		case InsArgType::SPELL_STR:
			os << "\"" << arg.GetSpellStr() << "\""; break;
		case InsArgType::OFFSET:
			os << arg.ofs_arg; break;
		case InsArgType::SUB_PASS_ARG:
			if (arg.sub_pass_arg.pass_type == 'i') {
				if (arg.sub_pass_arg.rcv_type == 'f')
					os << "(float)";
				os << "[" << arg.sub_pass_arg.passed_val.passed_iarg << "f]";
			}
			else {
				if (arg.sub_pass_arg.rcv_type == 'i')
					os << "(int)";
				os << "[" << arg.sub_pass_arg.passed_val.passed_farg << "]";
			}
			break;
		}
	return os;
}

std::istream& operator>>(std::istream& is, ECL_Include& ecl_include)
{
	is.read((char*)&ecl_include.mHeader, sizeof(ECL_IncludeHeader));

	int n_bytes=0;
	for (int i = 0; i < ecl_include.mHeader.num_files;i++) {
		char ch=0x0;
		std::string path="";
		do{
			is.read(&ch, 1); 
			n_bytes++;
			if(ch)
				path.push_back(ch);
		}
		while (ch);
		ecl_include.mIncludeFiles.push_back(path);
	}
	int pad = GetPadN(n_bytes, 4);
	if(pad)
		is.ignore(pad);
	return is;
}

std::istream& operator>>(std::istream& is, ECL_Ins& ecl_ins)
{
	is.read((char*)&ecl_ins.mHeader,sizeof(ECL_InsHeader));
	if (is.eof())
		return is;
	if (ecl_ins.mHeader.time == 0x484C4345){
		is.setstate(std::ios_base::failbit);
		return is;
	}
	ecl_ins.mArgs.resize((ecl_ins.mHeader.size-sizeof(ECL_InsHeader)) / sizeof(int32_t), 0);
	if(ecl_ins.mHeader.size - sizeof(ECL_InsHeader) != 0)
		is.read((char*)&(ecl_ins.mArgs[0]), ecl_ins.mHeader.size - sizeof(ECL_InsHeader));
	return is;
}

std::ostream& operator<<(std::ostream& os, ECL_Ins& ecl_ins)
{
	os.write((const char*)&ecl_ins.mHeader, sizeof(ECL_InsHeader));
	if(ecl_ins.mHeader.size - sizeof(ECL_InsHeader) !=0)
		os.write((char*)&(ecl_ins.mArgs[0]), ecl_ins.mHeader.size - sizeof(ECL_InsHeader));
	return os;
}


std::istream& operator>>(std::istream& is, ECL_Sub& ecl_sub)
{
	is.read((char*)&ecl_sub.mHeader,sizeof(ECL_SubHeader));

	while (true){
		ECL_Ins ins(is.tellg(), ecl_sub.mInses.size(), ecl_sub.mIndex);
		is >> ins;
		if (is.fail()){
			is.clear(std::ios_base::goodbit,true);
			break;
		}
		ecl_sub.mInses.push_back(ins);
	}
	return is;
}

std::istream& operator>>(std::istream& is, ECL_File& ecl_file)
{
	// is.seekg(0);
	is.read((char*)&ecl_file.mHeader, sizeof(ECL_DataHeader));
	ecl_file.mHeader.sub_count;

	is >> ecl_file.mAnmInclude>> ecl_file.mEclInclude;


	ecl_file.mSubPtrs.resize(ecl_file.mHeader.sub_count,0);
	is.read((char*)&(ecl_file.mSubPtrs[0]), ecl_file.mHeader.sub_count * sizeof(int32_t));


	int n_bytes = 0;
	for (int i = 0; i < ecl_file.mHeader.sub_count; i++) {
		char ch = 0x0;
		std::string name = "";
		do {
			is.read(&ch, 1);
			n_bytes++;
			if (ch)
				name.push_back(ch);
		} while (ch);
		ecl_file.mSubNames.push_back(name);
	}
	int pad = GetPadN(n_bytes, 4);
	if (pad)
		is.ignore(pad);

	for (int i = 0; i < ecl_file.mHeader.sub_count;i++) {
		int32_t ptr = ecl_file.mSubPtrs[i];
		is.seekg(ptr);
		ecl_file.mSubs.emplace_back(ptr,i,ecl_file.mSubNames[i]);
		is>>ecl_file.mSubs[ecl_file.mSubs.size() - 1];
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, ECL_Sub& ecl_sub)
{
	os.write((char*)&ecl_sub.mHeader, sizeof(ECL_SubHeader));
	for (int i = 0; i < ecl_sub.mInses.size(); i++){
		os << ecl_sub.mInses[i];
	}
	return os;
}

void ECL_File::GetInsList(std::vector<ECL_Ins>& out_inses)
{
	for (auto& sb : mSubs){
		for (auto& ins : sb.mInses){
			out_inses.push_back(ins);
		}
	}
}

int ECL_File::CalcSubIndexAt(int32_t address)
{
	int n = -2;
	for (int i = 0; i < mHeader.sub_count; i++) {
		int32_t ptr = mSubPtrs[i];
		if (address < ptr){
			n = i-1;
			break;
		}
	}
	if (n == -1)
		return -1; // ahead all subs
	if (n == -2)
		return mHeader.sub_count-1;
	return n;
}



std::string& ECL_Ins::GetInsHex()
{
	if (mInsHex != "")
		return mInsHex;
	std::stringstream ss;
	uint8_t* ch;
	{
		// int32_t time;
		// int16_t code;
		// int16_t size;
		// int16_t stack_mask;
		// int8_t diff_mask;
		// int8_t arg_count;
		// int32_t stack_count;
		int i;
		for (i = 0, ch= (uint8_t*)(&(mHeader.time)); i < sizeof(mHeader.time); i++)
			ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ch[i];
		ss << " ";
		for (i = 0, ch = (uint8_t*)(&(mHeader.code)); i < sizeof(mHeader.code); i++)
			ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ch[i];
		ss << " ";
		for (i = 0, ch = (uint8_t*)(&(mHeader.size)); i < sizeof(mHeader.size); i++)
			ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ch[i];
		ss << " ";
		for (i = 0, ch = (uint8_t*)(&(mHeader.stack_mask)); i < sizeof(mHeader.stack_mask); i++)
			ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ch[i];
		ss << " ";
		for (i = 0, ch = (uint8_t*)(&(mHeader.diff_mask)); i < sizeof(mHeader.diff_mask); i++)
			ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ch[i];
		ss << " ";
		for (i = 0, ch = (uint8_t*)(&(mHeader.arg_count)); i < sizeof(mHeader.arg_count); i++)
			ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ch[i];
		ss << " ";
		for (i = 0, ch = (uint8_t*)(&(mHeader.stack_count)); i < sizeof(mHeader.stack_count); i++)
			ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ch[i];
	}
	
	if (mArgs.size() != 0)
	{
		ss << " ";
		ch = (uint8_t*)(&mArgs[0]);
		for (int i = 0; i < mArgs.size() * sizeof(int32_t); i++) {
			if (i % 4 == 0)
				ss << " ";
			ss << std::hex << std::setw(2) << std::setfill('0') << (int32_t)ch[i];
		}
	}
	mInsHex = ss.str();
	return mInsHex;
}

std::vector<InsArg>& ECL_Ins::GetInsArgs(int version)
{
	if (has_dumped)
		return mArgsDumped;

	has_dumped = true;
	if (mArgs.size() == 0)
		return mArgsDumped;

	const char* fmt = GetFormat(version, mHeader.code);
	if (fmt == NULL)
		fmt = "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS";

	int8_t* parg = (int8_t*)&(mArgs[0]);
	int arg_maxsize = mArgs.size() * 4;
	int cur_size = 0;
	int cur_index = 0;
	for (const char* ch = fmt; *ch; )
	{
		InsArg cur_arg;
		cur_arg.is_stack = (1 << cur_index) & mHeader.stack_mask;
		switch (*ch)
		{
		default:
		case 't':
		case 'S':
			cur_arg.SetInt(*(int*)parg);
			parg += 4, cur_size += 4; ch++;
			break;
		case 'f':
			cur_arg.SetFloat(*(float*)parg);
			parg += 4,cur_size += 4; ch++;
			break;
		case'o':
			cur_arg.SetOffset(*(float*)parg);
			parg += 4, cur_size += 4; ch++;
			break;
		case'm':
		{
			int size = *(int*)parg;
			cur_arg.SetSubNameStr(size,(char*)(parg + 4));
			parg += 4 + size, cur_size += 4 + size; ch++;
		}break;
		case'x':
		{
			int size = *(int*)parg;
			cur_arg.SetSpellStr(size,(char*)(parg + 4));
			parg += 4 + size, cur_size += 4 + size; ch++;
		}break;
		case '*':
		{
			char type_pass = *(char*)(parg);
			char type_rcv = *(char*)(parg+1);
			if(type_pass=='i')
				cur_arg.SetSubPassArgInt(type_rcv,*(int*)(parg + 4));
			else
				cur_arg.SetSubPassArgInt(type_rcv, *(float*)(parg + 4));
			parg += 8, cur_size += 8;
			//do not inc ch
		}break;
		}
		mArgsDumped.push_back(cur_arg);

		cur_index++;
		if (cur_size >= arg_maxsize)
			break;
	}
	return mArgsDumped;
}


void loop_xor(uint8_t* data,size_t data_length,unsigned char key,unsigned char step,unsigned char step2){
	size_t i;
	for (i = 0; i < data_length; ++i) {
		const int ip = i - 1;
		data[i] ^= key + i * step + (ip * ip + ip) / 2 * step2;
	}
}
#include <iostream>
std::string InsArg::GetSpellStr()
{
	std::string str;
	str.reserve(spellstr_size);
	for (int i = 0; i < spellstr_size; i++)
		str.push_back(spellstr_arg[i]);
	loop_xor((uint8_t*) &(str[0]), spellstr_size, 0x77, 7, 16);
	return str;
}
