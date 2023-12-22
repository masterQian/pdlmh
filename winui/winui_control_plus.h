#pragma once
#include "winui_control.h"

#define DEFAULT_CONSTRUCT_COPY_MOVE(name) \
name(const name&) = default; \
name(name&&) = default; \
name& operator = (const name&) = default; \
name& operator = (name&&) = default

#define CONTROL_CONSTRUCT(name) \
name() noexcept = default; \
name(ID id_) noexcept : Control(id_) {} \
DEFAULT_CONSTRUCT_COPY_MOVE(name)

namespace winui::plus {
	// 唱片
	class Record : public Control {
	private:
		static constexpr Attr ControlType = 23119120;
		static Result __stdcall __RecordExCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4);
	public:
		CONTROL_CONSTRUCT(Record);
		Record(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 100, int height = 100, const Bin& image = {}) noexcept;
		void Image(const Bin& image) noexcept;
		void Angle(int angle) noexcept;
		void Start(UINT time) noexcept;
		void Stop() noexcept;
	};
}

#undef CONTROL_CONSTRUCT
#undef DEFAULT_CONSTRUCT_COPY_MOVE