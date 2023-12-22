#pragma once
#include "winui_base.h"

#define DELETE_MOVE_COPY_CONSTRUCT(name) \
name() noexcept = default; \
name(const name&) = delete; \
name(name&&) = delete; \
name& operator = (const name&) = delete; \
name& operator = (name&&) = delete

namespace winui {
	// 菜单
	class Menu {
		static constexpr Attr MenuId_IconWidth_Get = 1;
		static constexpr Attr MenuId_IconHeight_Get = 2;
		static constexpr Attr MenuId_Transparency_Get = 4;
		static constexpr Attr MenuId_Skin_Get = 8;
		static constexpr Attr MenuId_Font_Get = 16;
		static constexpr Attr MenuId_Cursor_Get = 32;
		static constexpr Attr MenuId_IconWidth_Set = 1;
		static constexpr Attr MenuId_IconHeight_Set = 2;
		static constexpr Attr MenuId_Transparency_Set = 32;
		static constexpr Attr MenuId_Skin_Set = 4;
		static constexpr Attr MenuId_Font_Set = 8;
		static constexpr Attr MenuId_Cursor_Set = 16;
	private:
		ID id = 0;
		int mWidth = 60;
	public:
		// 菜单项
		class Separate;
		class Item {
			friend class Separate;
			ID menuId = 0, id = 0;
		public:
			constexpr Item() noexcept = default;
			constexpr Item(ID menuId_, ID id_) noexcept : menuId{ menuId_ }, id{ id_ }{}
			Item(Menu& menu, ConstString title, short tag = 0, const ICO& icon = {},
				int index = -1, int sonWidth = 60, int height = 35, ARGB fontColor = Color::Black,
				ARGB disabledFontColor = Color::Gray, bool disabled = false) noexcept;
			Item(const Item& item, ConstString title, short tag = 0, const ICO& icon = {},
				int index = -1, int sonWidth = 60, int height = 35, ARGB fontColor = Color::Black,
				ARGB disabledFontColor = Color::Gray, bool disabled = false) noexcept;
			// 销毁
			void Destroy() noexcept;
			String Title() const noexcept;
			void Title(ConstString title) noexcept;
			ICO Icon() const noexcept;
			void Icon(const ICO& icon) noexcept;
			ARGB FontColor() const noexcept;
			void FontColor(ARGB fontColor) noexcept;
			ARGB DisabledFontColor() const noexcept;
			void DisabledFontColor(ARGB disabledFontColor) noexcept;
			int Height() const noexcept;
			void Height(int height) noexcept;
			bool Disabled() const noexcept;
			void Disabled(bool disabled) noexcept;
			// 取子菜单数
			int Count() const noexcept;
			// 取子菜单
			Item Child(int index) const noexcept;
			// 取子菜单宽度
			int ChildWidth() const noexcept;
			// 取标记
			short Tag() const noexcept;
			constexpr bool operator == (Item other) const noexcept { return menuId == other.menuId && id == other.id; }
			constexpr operator ID() const noexcept { return id; }
		};

		// 分割线
		class Separate {
			ID menuId = 0, id = 0;
		public:
			constexpr Separate(ID menuId_, ID id_) noexcept : menuId{ menuId_ }, id{ id_ }{}
			Separate(Menu& menu, int index = -1, int height = 10) noexcept;
			Separate(const Item& item, int index = -1, int height = 10) noexcept;
			void Destroy() noexcept;
		};

		using MenuExCall = void(__stdcall*)(Item item, Event msg, short tag);
	public:
		DELETE_MOVE_COPY_CONSTRUCT(Menu);
		// 绑定(先绑定回调再设置其他属性)
		Menu& Bind(MenuExCall callback, int width = 60, int iconWidth = 0, int iconHeight = 0) noexcept;
		int IconWidth() const noexcept;
		Menu& IconWidth(int iconWidth) noexcept;
		int IconHeight() const noexcept;
		Menu& IconHeight(int iconHeight) noexcept;
		int Transparency() const noexcept;
		Menu& Transparency(int transparency) noexcept;
		Bin Skin() const noexcept;
		Menu& Skin(const Bin& skin) noexcept;
		Bin Font() const noexcept;
		Menu& Font(const Bin& font) noexcept;
		Bin Cursor() const noexcept;
		Menu& Cursor(const Bin& cursor) noexcept;
		// 销毁
		void Destroy() noexcept;
		// 是否弹出
		bool IsOpen() const noexcept;
		// 弹出
		void Open() const noexcept;
		// 关闭
		void Close() const noexcept;
		// 取子菜单数
		int Count() const noexcept;
		// 取子菜单
		Item Child(int index) const noexcept;
		// 取子菜单宽度
		constexpr int ChildWidth() const noexcept { return mWidth; }
		constexpr operator ID() const noexcept { return id; }
		constexpr void __Src(int _width, ID _id) noexcept { mWidth = _width; id = _id; }
		static Call __GetInternalCall() noexcept;
	};
}

#undef DELETE_MOVE_COPY_CONSTRUCT