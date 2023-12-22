#include "../include/util.h"

ByteArray HICON_PNG(HICON hIcon) noexcept {
	IStream* istream{};
	Gdiplus::Bitmap hBitmap(hIcon);
	ULARGE_INTEGER ulnSize;
	HRESULT hResult = CreateStreamOnHGlobal(nullptr, true, &istream);
	hBitmap.Save(istream, &var->GUID_PNG, nullptr);
	istream->Seek({ 0 }, STREAM_SEEK_END, &ulnSize);
	istream->Seek({ 0 }, STREAM_SEEK_SET, nullptr);
	UINT size = static_cast<UINT>(ulnSize.QuadPart);
	ByteArray png(size + 8); auto pBytes = png.data(); int* pInt = (int*)pBytes;
	pInt[0] = 0; pInt[1] = size;
	ULONG bytesRead;
	istream->Read(pBytes + 8, size, &bytesRead);
	istream->Seek({ 0 }, STREAM_SEEK_SET, nullptr);
	istream->Release();
	return png;
}

void LoadFileEntry(ConstString str, FileEntry& entry) noexcept {
	ConstStr p1 = str.data(), p2 = p1;
	while (*p2 != LS::Split) ++p2;
	entry.name.assign(p1, p2); p1 = ++p2;
	while (*p2 != LS::Split) ++p2;
	entry.path.assign(p1, p2); p1 = ++p2;
	entry.admin = *p1 == LS::CTrue; p1 = p2 = p1 + 2;
	while (*p2 != LS::Split) ++p2;
	entry.arg.assign(p1, p2); p1 = p2 + 1;
	entry.type = StringTo<int>(p1);
	if (entry.type == 0) {
		if (auto hIcon = ExtractIconW(nullptr, entry.path.data(), 0)) {
			auto bs = HICON_PNG(hIcon);
			entry.ico = ICO::FromEByteSet(bs.data() + 8);
			DeleteObject(hIcon);
		}
		else entry.ico = res->Ico.Default[0];
	}
	else entry.ico = res->Ico.Default[entry.type];
}

String SaveFileEntry(const FileEntry& entry) noexcept {
	return ToString(entry.name, LS::SSplit, entry.path,
		(entry.admin ? LS::SplitTrue : LS::SplitFalse),
		entry.arg, LS::SSplit, entry.type);
}

int GetFileExtraType(ConstString ext) noexcept {
	String lower = ext;
	for (auto& i : lower)
		if (i >= L'A' && i <= L'Z') i += L'a' - L'A';
	if (auto iter = var->TypeMap.find(ext); iter != var->TypeMap.cend()) return iter->second;
	return 1;
}

ICO GetFileExtraTypeIcon(ConstString path, int* rType) noexcept {
	auto fn = path.data();
	DWORD attr = GetFileAttributesW(fn);
	if (attr != INVALID_FILE_ATTRIBUTES) {
		if ((attr & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) {
			wchar_t ext[_MAX_EXT]{};
			_wsplitpath_s(fn, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
			int type = GetFileExtraType(ext);
			if (type == 0) {
				if (auto hIcon = ExtractIconW(nullptr, fn, 0)) {
					auto bs = HICON_PNG(hIcon);
					auto ico = ICO::FromEByteSet(bs.data() + 8);
					DeleteObject(hIcon);
					if (rType) *rType = 0;
					return ico;
				}
				if (rType) *rType = 1;
				return res->Ico.Default[0];
			}
			if (rType) *rType = type;
			return res->Ico.Default[type];
		}
		if (rType) *rType = 2;
		return res->Ico.Default[2];
	}
	*rType = 1;
	return {};
}