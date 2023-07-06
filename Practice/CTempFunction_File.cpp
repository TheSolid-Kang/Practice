#include "CTempFunction_File.h"
#include <list>

#if UNICODE 
using TString = std::wstring;
#define to_tstring   to_wstring
#else
using TString = std::string;
#define to_tstring   to_string
using TString = std::string;
#endif;
CTempFunction_File::CTempFunction_File()
{

}

CTempFunction_File::~CTempFunction_File()
{

}

void CTempFunction_File::_Initialize()
{
  auto arr_title = _BuildArray( _T("1. 특정 확장자의 파일 목록 생성")
    , _T("")
    , _T("")
    , _T("99. EXIT") );
  m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
  _InitFunc();
  _InitSelectedFunc();
}

void CTempFunction_File::_InitFunc(void)
{
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::SET_FILE_INI), [&](const void* _p_void) -> std::shared_ptr<void> {
    TString exePath = CFileMgr::GetEXEFilePath();
    TString dirPath = exePath + _T("\\File");
    TString settingIniPath = dirPath + _T("\\Setting.ini");
    //실행 경로에 File 폴더가 없는 경우 File 폴더 생성
    if (false == std::filesystem::is_directory(dirPath))
      CFileMgr::CreateDirectorys(dirPath);

    //File 폴더에 Setting.ini가 없는 경우 Setting.ini파일 생성한 후 내용 채워넣음.
    if (false == std::filesystem::exists(settingIniPath))
    {
      CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("FILE_TYPE"), _T(".md"), settingIniPath);
      CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("ARR_KEYWORD"), _T("검색어"), settingIniPath);
    }
    auto temp = CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("SEARCH_KEYWORD"), settingIniPath);

    return nullptr; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_FILE_LIST), [&](const void* _p_void) -> std::shared_ptr<void> {
    TCHAR* fileType = ((TCHAR*)(_p_void));
    TString directoryPath = CFileMgr::GetOpenFolderDialg(_T("D:\\TheSolid_KANG\\Export-aa366e9e-ed18-45f1-bd9e-76939f7b003a"));
    auto vecFiles = CFileMgr::GetRecursiveFilesInDirectory(directoryPath);

    std::list<TString> listFiles(vecFiles.begin(), vecFiles.end());

    listFiles.remove_if([&listFiles, fileType](const TString& _path) 
      -> bool {return std::string::npos == _path.find(fileType); 
      });
    return std::make_shared<std::list<TString>>(listFiles); }));

}


void CTempFunction_File::_InitSelectedFunc(void)
{
  /// <summary>
  /// 1. 폴더 선택
  /// 2. 선택된 폴더에서 파일 확장자가(xxx)인 list 생성
  /// 3. list 컨테이너에 담긴 파일 읽고, 검색어가 담겨 있으면 file명과 파일 내용을 map 컨테이너에 추가
  /// 
  /// </summary>
  /// <param name=""></param>
  m_map_selected_func.emplace(std::make_pair(static_cast<size_t>(SELECTED_FUNC::FIND_FILE), [&](const void* _p_void) -> std::shared_ptr<void> {

    m_map_func[static_cast<size_t>(FUNC::SET_FILE_INI)](nullptr);
    auto sharFileList = m_map_func[static_cast<size_t>(FUNC::GET_FILE_LIST)](_T(".md"));
    auto& listFilePath = *(std::list<TString>*)sharFileList.get();

    std::map<TString, std::map<TString, int>> mapCount;

    //1. 검색어 설정
    //auto search_key = CIO::ask_and_return_string(); //잘 안 됨.
    TString arrKeword = CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("ARR_KEYWORD"), CFileMgr::GetEXEFilePath() + _T("\\FILE\\Setting.ini"));
    auto vecKeyword = CMyEtc::Split(arrKeword, _T('|'));

    //2. 각각의 파일들 내에서 검색 횟수 확인
    //  1) 컨테이너에서 caleb_path 선택
    for (const TString& _caleb_path : listFilePath)
    {
      //  2) caleb.txt 파일에 담긴 모든 내용 입력
      TString caleb = CFIOMgr::GetFileLines(_caleb_path);
      for (TString _searchKeyword : vecKeyword)
      {
        //  3) 한 Caleb에서 검색어 별 언급횟수 확인 및 입력
        auto unitVecAddress = KMP::GetSearchedAddress(caleb, _searchKeyword);
        if ((*unitVecAddress).size() != 0)
          mapCount[_caleb_path][_searchKeyword] += (*unitVecAddress).size();
      }
    }

    std::map<TString, int> mapTotalCount;

    //3. Console창에 각각의 파일에서 검색어 별 언급횟수 출력
    for (std::pair<TString, std::map<TString, int>> _pair_cnt : mapCount)
    {
      CTempFunction::_Render(_T("=====") + _pair_cnt.first + _T("====="));
      for (std::pair<TString, int> _pair : _pair_cnt.second)
      {
        CTempFunction::_Render(_T("    ") + _pair.first + _T(" == ") + std::to_tstring(_pair.second));
        mapTotalCount[_pair.first] += _pair.second;
      }
    }

    //4. 전체 언급횟수 확인
    for (std::pair<TString, int> _pair : mapTotalCount)
      CTempFunction::_Render(_T("KEY: ") + _pair.first + _T("  |  VALUE: ") + std::to_tstring(_pair.second) + _T("개"));

    //std::map<TString, TString> mapSearchedFiles;
    //std::for_each(listFile.begin(), listFile.end(),
    //  [&mapSearchedFiles, vecKeyword](const TString& _filePath) {
    //    auto contents = CFIOMgr::GetFileLines(_filePath);


    //  });


    return nullptr; }));

}


void CTempFunction_File::_Render()
{
	auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE)](nullptr);
	CTempFunction::_Render(*(TString*)shar_title.get());
}

void CTempFunction_File::_Render(const void* _p_void)
{
}

int CTempFunction_File::_Update(int _event)
{
  m_map_selected_func[static_cast<size_t>(_event)](nullptr);
  return 0;
}

void CTempFunction_File::_Release()
{
}
