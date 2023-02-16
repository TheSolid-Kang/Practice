#include "CPractice_2.h"
#include "../MySQL_DAO_v2/MySQL_DAO_v2.hpp"
#include "../MySQL_DAO_v2/MySQL_DAO_v3.h"
#include <numeric> //accumulate 사용

#include "KMP.h"
#include <tuple>


CPractice_2::CPractice_2()
	: m_uniq_map_func(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
	, m_uniq_map_testfunc(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
{

}

CPractice_2::~CPractice_2()
{
}

void CPractice_2::_Initialize()
{
	auto arr_title = _BuildArray(_T(" ")
		, _T("1. TwoMites 스키마의 bible 테이블에 데이터 넣기")
		, _T("2. DAO 테스트")
		, _T("")
		, _T("99. EXIT") );
	m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
	_InitFunc();
	_InitSelectedFunc();
}

void CPractice_2::_Render() 
{
	std::for_each(m_list_title.cbegin(), m_list_title.cend(), [&](const TString& _title) {std::tcout << _title << std::endl; });
}

void CPractice_2::_Render(const void* _p_void)
{
}

int CPractice_2::_Update(int _event)
{
	switch (CIO::ask_and_return_integer())
	{
	case static_cast<size_t>(TEST_FUNC::ONE):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::ONE)](nullptr);
		break;
	case static_cast<size_t>(TEST_FUNC::TWO):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::TWO)](nullptr);
		break;
	case static_cast<size_t>(TEST_FUNC::THREE):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::THREE)](nullptr);
		break;
	case static_cast<size_t>(TEST_FUNC::FOUR):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::FOUR)](nullptr);
		break;
	case static_cast<size_t>(TEST_FUNC::FIVE):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::FIVE)](nullptr);
		break;

	default:
		break;
	}

	return 0;
}

void CPractice_2::_Release()
{
}

void CPractice_2::_InitFunc(void)
{
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::ONE)
		, [&](const void* _p_void) {
			//성경 경로 
			auto path = CFileMgr::GetOpenFileDialg();

			//성경 txt에 담긴 내용 절별로 vector 컨테이너에 담기
			auto vecBible = CFIOMgr::GetVecFileLines(path);

			//성경(bible), 장(chapter), 절(verse), 말씀(description)
			std::vector<std::tuple<TString, TString, TString, TString>> vecBibleLine;
			vecBibleLine.reserve(31101);
			TString bible = _T("");
			TString chapter = _T("");
			TString verse = _T("");
			TString description = _T("");

			for (auto line : vecBible)
			{
				auto colonIndex = line.find(_T(":"));
				auto spaceIndex = line.find(_T(" "));
				int chapterIndex = 0;

				for (int i = colonIndex - 1; i >= 0; --i)
				{
					auto temp = line[i];
					if (temp > 57 || temp < 48)
					{
						chapterIndex = i + 1;
						break;
					}
				}

				bible = line.substr(0, chapterIndex);
				chapter = line.substr(chapterIndex, colonIndex - chapterIndex);
				verse = line.substr(colonIndex + 1, spaceIndex - colonIndex - 1);
				description = line.substr(spaceIndex + 1, line.length() - spaceIndex);

				vecBibleLine.push_back(std::make_tuple(bible, chapter, verse, description));
			}
			vecBible.clear();

			StringBuilder strbuil(49999);
			std::vector<TString> vecInsertQuery;
			for (auto line : vecBibleLine)
			{
				if (49000 > strbuil.size())
				{
					strbuil.append(_T(", ("));
					strbuil.append(_T("'") + std::get<0>(line) + _T("', "));
					strbuil.append(_T("") + std::get<1>(line) + _T(", "));
					strbuil.append(_T("") + std::get<2>(line) + _T(", "));
					strbuil.append(_T("'") + std::get<3>(line) + _T("', "));
					strbuil.append(_T("'") + std::get<0>(line) + std::get<1>(line) + _T(":") + std::get<2>(line) + std::get<3>(line) + _T("' "));
					strbuil.append_endl(_T(")"));
				}
				else
				{
					auto front = _T("INSERT INTO bible (b_book, b_chapter, b_verse, b_descript, b_full_descript) VALUES \n");
					auto query = strbuil.str();
					vecInsertQuery.push_back(front + query.substr(1, query.length() - 1) + _T(";"));
					strbuil.clear();
				}
			}

			auto front = _T("INSERT INTO bible (b_book, b_chapter, b_verse, b_descript, b_full_descript) VALUES \n");
			auto query = strbuil.str();
			vecInsertQuery.push_back(front + query.substr(1, query.length() - 1) + _T(";"));

			//230216_tk dao_3는 한글 입력이 불가능한 문제가 있음...
			// 테이블에 insert 한 때 한글 전부 깨짐
			//auto dao = MySQL_DAO_v3();
			//std::for_each(vecInsertQuery.cbegin(), vecInsertQuery.cend(), [&dao](const TString& _query) { dao.Execute(_query); });
			//dao.ExecuteTransaction(vecInsertQuery);

			path = CFileMgr::GetEXEFilePath() + _T("\\sql.txt");
			CFileMgr::CreateNewFile(path);
		
			std::for_each(vecInsertQuery.cbegin(), vecInsertQuery.cend(), [path](const TString& _query) { CFIOMgr::WriteAddingText(path, _query + _T("\n")); });
			

			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::TWO)
		, [&](const void* _p_void) {
#ifdef Release
			MySQL_DAO_v3 dao;
			auto query = _T("INSERT INTO bible (b_book, b_chapter, b_verse, b_descript, b_full_descript) VALUES  ('창', '1', '1', '태초에 하나님이 천지를 창조하시니라', '창1:1태초에 하나님이 천지를 창조하시니라');");
			dao.Execute(query);
#endif

			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::THREE)
		, [&](const void* _p_void) {

			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FOUR)
		, [&](const void* _p_void) {

			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FIVE)
		, [&](const void* _p_void) {
			
			return nullptr; }));
}

void CPractice_2::_InitSelectedFunc(void)
{
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::ONE)
	, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::ONE)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::TWO)
		, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::TWO)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::THREE)
		, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::THREE)](nullptr);
	return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::FOUR)
		, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::FOUR)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::FIVE)
		, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::FIVE)](nullptr);
			return nullptr; }));


}


