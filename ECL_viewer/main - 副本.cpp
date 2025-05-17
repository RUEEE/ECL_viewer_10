#include "window.h"
#include "ECLdump.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <format>

bool WindowUpdateFunc(ImGuiWindow* pWind)
{
	static std::wstring file_path;
	static ECL_File ecl;
	static int ver = 18;
	static std::vector<int8_t> selected_ins;
	static std::vector<int8_t> selected_sub;

	if (ImGui::Button("open"))
	{
		OPENFILENAME ofn = { 0 };
		WCHAR ppath[MAX_PATH] = { 0 };
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrFilter = L"ecl(*.ecl)\0*.ecl\0*.*\0\0";
		ofn.lpstrFile = ppath;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		if (GetOpenFileName(&ofn)) {
			file_path = std::wstring(ppath);
		}
	}
	ImGui::SameLine();
	ImGui::Text("%ws", file_path.c_str());

	ImGui::SetNextItemWidth(150.0f);
	ImGui::InputInt("version", &ver);
	ImGui::SameLine();
	if (ImGui::Button("analyze")) {
		ecl.Clear();
		std::fstream fs(file_path, std::ios::in | std::ios::binary);
		if (fs.is_open()) {
			fs >> ecl;
			ecl.version = ver;
			fs.close();
		}
		int i = 0, j = 0;
		for (auto& sub : ecl.mSubs)
		{
			sub.mView_Index = j;
			for (auto& ins : sub.mInses)
			{
				ins.mView_Index = i;
				i++;
			}
			j++;
		}
			
		selected_ins.clear();
		selected_ins.resize(i, false);
		selected_sub.clear();
		selected_sub.resize(ecl.mSubs.size(), false);
	}
	ImGui::Separator();

	static char jmpto_text[100] = { 0 };
	ImGui::SetNextItemWidth(150.0f);
	

	ImGui::InputText("jumpto", jmpto_text,100);
	ImGui::SameLine();
	int jmpto_ins = -1;
	if (ImGui::Button("jump")){
		int32_t jmp;
		if (sscanf_s(jmpto_text, "%x", &jmp))
		{
			int nins=0;
			int nsub = 0;
			for (auto& sub : ecl.mSubs){

				for (auto& ins : sub.mInses){
					if (ins.mOfs <= jmp && ins.mOfs+ins.mHeader.size > jmp) {
						goto LBL_FIND;
					}
					nins++;
				}
				nsub++;
			}
			goto LBL_NOFIND;
		LBL_FIND:
			memset(&(selected_ins[0]), 0, selected_ins.size());
			selected_sub[nsub] = true;
			selected_ins[nins] = true;
			jmpto_ins = nins;
		LBL_NOFIND:
			1;
		}
	}

	if (ecl.mHeader.sig[0] == 'S')//SCPT
	{
		for (auto& sub : ecl.mSubs) {
			ImGui::Columns(1);
			ImGui::SetNextItemOpen(selected_sub[sub.mView_Index]);
			if (ImGui::CollapsingHeader(std::format("({:X})sub {}##{}", sub.mOfs, sub.mName, sub.mIndex).c_str())){
				if (ImGui::Button("copy to clipboard"))
				{
					std::stringstream ss;
					ss << sub;
					auto str=ss.str();
					std::stringstream out;
					for (int i = 0; i < str.size();i++) {
						unsigned char ch = str[i];
						out << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int32_t)ch;
						if(i<str.size()-1)
							out<< ",";
						if (i % 50 == 49)
							out << "\n";
					}
					ImGui::SetClipboardText(out.str().c_str());
				}
				selected_sub[sub.mView_Index] = true;
				ImGui::BeginTable(std::format("{}##{}", sub.mName, sub.mIndex).c_str(), 3, ImGuiTableFlags_::ImGuiTableFlags_Resizable);
				
				for (auto& ins : sub.mInses) {
					ImGui::TableNextRow();

					if (jmpto_ins == ins.mView_Index)
						ImGui::SetScrollHereY();
					ImGui::TableNextColumn();
					if (ImGui::Selectable(std::format("{:X}(code={:X},arg={:X})##{}_1", ins.mOfs, ins.mOfs + 0x4,ins.mOfs + sizeof(ins.mHeader), ins.mView_Index).c_str(), selected_ins[ins.mView_Index], ImGuiSelectableFlags_SpanAllColumns)) {
						memset(&(selected_ins[0]), 0, selected_ins.size());
						selected_ins[ins.mView_Index] = true;
					}

					ImGui::TableNextColumn();
					// ImGui::Selectable(std::format("{}##{}_2", ins.GetInsHex(), index_ins).c_str(),false);
					ImGui::Text("%s", ins.GetInsHex().c_str());

					ImGui::TableNextColumn();
					auto args = ins.GetInsArgs(ecl.version);
					std::stringstream ss;
					for (int i = 0; i < args.size(); i++)
					{
						ss << args[i];
						if (i != args.size() - 1)
							ss << ", ";
					}
					// ImGui::Selectable(std::format("ins_{}({})##{}_2", ins.mHeader.code, ss.str(), index_ins).c_str(), false);
					ImGui::Text("ins_%d(%s)", ins.mHeader.code, ss.str().c_str());
				}
				ImGui::EndTable();
			}else{
				selected_sub[sub.mView_Index] = false;
			}
		}
	}

	return false;
}

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pCmdLine,
	_In_ int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CON", "r", stdin);
	freopen_s(&stream, "CON", "w", stdout);
#endif

	ImGuiWindowInfo info = { 0 };
	info.className = L"windClass";
	info.title = L"wind";
	info.hInstance = hInstance;
	info.initialWidth = 640;
	info.initialHeight = 480;
	info.maxWidth = 1280;
	info.maxHeight = 960;
	info.updateFunc = WindowUpdateFunc;

	auto res = ImGuiWindow::CreateGuiWindow(info);
	if (FAILED(res)) {
		return res;
	}

	ImGuiWindow::GetWindow()->Update();

	return 0;
}
