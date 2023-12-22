#pragma once
#include "winui_base.h"

#define DELETE_MOVE_COPY_CONSTRUCT(name) \
name() noexcept = default; \
name(const name&) = delete; \
name(name&&) = delete; \
name& operator = (const name&) = delete; \
name& operator = (name&&) = delete

namespace winui {
	// 计时器
	template<typename clock_type = std::chrono::system_clock>
	class Timer {
		clock_type::time_point mTick;
	public:
		constexpr Timer() noexcept { mTick = clock_type::now(); }
		constexpr UINT Tick() noexcept {
			typename clock_type::time_point last = mTick;
			mTick = clock_type::now();
			return std::chrono::duration_cast<std::chrono::milliseconds>(mTick - last).count();
		}
	};

	// 编码转换
	class Code final {
		Code() = delete;
	public:
		using CodePage = UINT;
		static constexpr CodePage ANSI = CP_ACP;
		static constexpr CodePage UTF8 = CP_UTF8;
	public:
		// 字节流转字符串
		static String From(const ByteSet& bs, CodePage codePage = UTF8) noexcept;
		// 字节数组转字符串
		static String From(const ByteArray& data, CodePage codePage = UTF8) noexcept;
		// 字符串转字节数组
		static ByteArray To(ConstString data, CodePage codePage = UTF8) noexcept;
	};

	// 文件操作
	class File final {
		File() = delete;
	public:
		// 读字节数组
		static ByteArray ReadByteArray(ConstString path) noexcept;
		// 读字符串
		static String ReadString(ConstString path, Code::CodePage codePage = Code::UTF8) noexcept;
		// 读字节集
		static Bin ReadBin(ConstString path) noexcept;
		// 读位图
		static ICO ReadICO(ConstString path) noexcept;
		// 写字节数组
		static bool WriteByteArray(const ByteArray& ba, ConstString path) noexcept;
		// 写字符串
		static bool WriteString(ConstString str, ConstString path, Code::CodePage codePage = Code::UTF8) noexcept;
		// 写字节集
		static bool WriteBin(const Bin& bin, ConstString path) noexcept;
		// 写位图
		static bool WriteICO(const ICO& ico, ConstString path) noexcept;
	};

	// 加解密
	class Crypt final {
		Crypt() = delete;
	public:
		// 取MD5
		static String MD5(ConstBytes bin, UINT len) noexcept;
		static String MD5(const ByteArray& bin) noexcept;
		static String MD5(ConstString s, Code::CodePage codePage = Code::UTF8) noexcept;
		// Base64加密
		static String Base64Encode(ConstBytes bin, UINT len) noexcept;
		static String Base64Encode(const ByteArray& bin) noexcept;
		static String Base64Encode(ConstString s, Code::CodePage codePage = Code::UTF8) noexcept;
		static ByteArray Base64Decode(ConstString s) noexcept;
	};

	// 注册表操作
	class Reg {
		HKEY hKey = nullptr;
	private:
		static REGSAM dwSign;
	public:
		static constexpr HKEY ClassesRoot = HKEY_CLASSES_ROOT;
		static constexpr HKEY CurrentUser = HKEY_CURRENT_USER;
		static constexpr HKEY LocalMachine = HKEY_LOCAL_MACHINE;
		static constexpr HKEY Users = HKEY_USERS;
		static constexpr HKEY CurrentConfig = HKEY_CURRENT_CONFIG;
	public:
		DELETE_MOVE_COPY_CONSTRUCT(Reg);
		Reg(HKEY base, ConstString path) noexcept;
		// 是否打开
		constexpr bool isOpen() noexcept { return hKey != nullptr; }
		// 打开
		bool Open(HKEY base, ConstString path) noexcept;
		// 关闭
		bool Close() noexcept;
		// 创建项
		bool CreateItem(ConstString item, Reg* ret = nullptr) noexcept;
		// 删除项
		bool DeleteItem(ConstString item) noexcept;
		// 枚举项
		void EnumItem(void(*callback)(ConstString)) noexcept;
		// 键是否存在
		bool isKeyExists(ConstString key) noexcept;
		// 取二进制值
		ByteArray GetBinaryValue(ConstString key) noexcept;
		// 取数值值
		UINT GetNumberValue(ConstString key) noexcept;
		// 取字符串值
		String GetStringValue(ConstString key) noexcept;
		// 置二进制值
		bool SetBinaryValue(ConstString key, ConstBytes value, UINT size, DWORD type = REG_BINARY) noexcept;
		// 置数值值
		bool SetNumberValue(ConstString key, UINT value) noexcept;
		// 置字符串值
		bool SetStringValue(ConstString key, ConstString value) noexcept;
		// 删除键
		bool DeleteKey(ConstString key) noexcept;
		// 枚举键值
		void EnumKeyValue(void(*callback)(ConstString, ConstString)) noexcept;
		// 刷新环境变量
		static void FlushEnvironment() noexcept;
	};

	// 剪贴板
	class ClipBoard final {
		ClipBoard() = delete;
	public:
		// 清空剪贴板
		static void Empty() noexcept;
		// 取剪贴板字符串
		static String GetString() noexcept;
		// 置剪贴板字符串
		static void SetString(ConstString str) noexcept;
		// 取剪贴板位图
		static ByteArray GetBitmap() noexcept;
		// 置剪贴板文件
		static void SetFile(std::vector<String> files) noexcept;
	};

	// 配置项操作
	class Ini {
	public:
		using Section = std::unordered_map<String, String>;
		using IniGroup = std::unordered_map<String, Section>;
		IniGroup group;
	public:
		DELETE_MOVE_COPY_CONSTRUCT(Ini);
		// 从内存读入
		bool LoadMemory(ConstString data) noexcept;
		// 从文件读入
		bool LoadFile(ConstString filename, Code::CodePage codePage = Code::UTF8) noexcept;
		// 保存到内存
		String SaveMemory() const noexcept;
		// 保存到文件
		bool SaveFile(ConstString filename, Code::CodePage codePage = Code::UTF8) const noexcept;
		// 取配置节
		Section& operator [] (ConstString name) noexcept { return group[name]; }
	};

	// 路径
	class Path final {
		Path() = delete;
	public:
		using PathToken = UINT;
		static constexpr PathToken Desktop = 0x0000U;
		static constexpr PathToken Documents = 0x0005U;
		static constexpr PathToken Fonts = 0x0014U;
		static constexpr PathToken AppData = 0x001AU;
		static constexpr PathToken Windows = 0x0024U;
		static constexpr PathToken System = 0x0025U;
		static constexpr PathToken ProgramFiles = 0x0026U;
	public:
		// 自动调节当前文件夹
		static void AutoCurrentFolder() noexcept;
		// 保证文件夹存在
		static bool MakesureFolder(ConstString path) noexcept;
		// 保证文件存在
		static bool MakesureFile(ConstString path, const ByteArray& content = {}) noexcept;
		// 取快捷方式目标
		static String GetShortCutTarget(ConstString path) noexcept;
		// 取特定目录
		static String GetPath(PathToken token) noexcept;
	};

	// 进程
	class Process final {
		Process() = delete;
	public:
		// 单例程序模式
		static bool LockSelf() noexcept;
		// 执行
		static void Execute(ConstString path, ConstString arg = {}, bool isAdmin = false) noexcept;
	};

	// 系统
	class System final {
		System() = delete;
	public:
		// 取驱动器名称列表
		static std::vector<String> GetDriversList() noexcept;
		// 取图像编码器列表
		static std::unordered_map<String, CLSID> GetImageEncoder() noexcept;
	};

	// 回收站
	class RecycleBin final {
		RecycleBin() = delete;
	public:
		// 清空回收站
		static void Clear() noexcept;
		// 回收站是否为空
		static bool IsEmpty() noexcept;
	};

	// 屏幕
	class Screen final {
		Screen() = delete;
	public:
		static int Width; // 屏幕宽
		static int Height; // 屏幕高
		static int TaskBarHeight; // 任务栏高
	private:
		static bool initialize;
	};
}

#undef DELETE_MOVE_COPY_CONSTRUCT