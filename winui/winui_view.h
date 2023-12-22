#pragma once
#include "winui_control.h"

#define DELETE_MOVE_COPY_CONSTRUCT(name) \
name() noexcept = default; \
name(const name&) = delete; \
name(name&&) = delete; \
name& operator = (const name&) = delete; \
name& operator = (name&&) = delete

namespace winui {
	// 互斥锁
	class Mutex {
		volatile bool sign = true;
	public:
		inline constexpr Mutex() noexcept = default;
		inline constexpr volatile bool lock() noexcept {
			if (sign) {
				sign = false;
				return true;
			}
			return false;
		}
		inline constexpr void unlock() noexcept { sign = true; }
		inline constexpr operator volatile bool() const noexcept { return sign; }
	};

	// 异步任务
	class SyncTask {
		SyncTask() = delete;
	public:
		using Runnable = void(*)() noexcept;
		static void Start(Runnable run) noexcept;
	};
}

namespace winui {
	// 时钟
	class Clock {
		HWND hwnd = nullptr;
	public:
		DELETE_MOVE_COPY_CONSTRUCT(Clock);
		// 绑定
		void Bind(const Window& window, int duration = 0) noexcept;
		// 启动
		void Start(int duration) noexcept;
		// 停止
		void Stop() noexcept;
		// 销毁
		void Destroy() noexcept;
		// 判定
		constexpr bool Check(Arg arg1) const noexcept { return arg1 == (Arg)this; }
	};

	// 热键
	class HotKey {
		HWND hwnd = nullptr;
	public:
		static constexpr Attr WithKey_Null = 0;
		static constexpr Attr WithKey_ALT = MOD_ALT;
		static constexpr Attr WithKey_CTRL = MOD_CONTROL;
		static constexpr Attr WithKey_SHIFT = MOD_SHIFT;
		static constexpr Attr WithKey_WIN = MOD_WIN;
	public:
		DELETE_MOVE_COPY_CONSTRUCT(HotKey);
		// 绑定
		void Bind(const Window& window, Attr key, Attr withKey = WithKey_Null) noexcept;
		// 销毁
		void Destroy() noexcept;
		// 判定
		constexpr bool Check(Arg arg1) const noexcept { return arg1 == (Arg)this; }
	};

	// 托盘
	class Tray {
		HWND hwnd = nullptr;
	public:
		DELETE_MOVE_COPY_CONSTRUCT(Tray);
		// 绑定
		void Bind(const Window& window, const Bin& icon = {}, ConstString text = {}) noexcept;
		// 销毁
		void Destroy() noexcept;
	};

	// 拖放
	class Drag {
		HWND hwnd = nullptr;
	public:
		using DragPath = wchar_t(*)[MAX_PATH];
		DELETE_MOVE_COPY_CONSTRUCT(Drag);
		// 绑定
		void Bind(const Window& window) noexcept;
		// 销毁
		void Destroy() noexcept;
	};
}

namespace winui {
	// 剪辑版监听器
	class ClipMonitor {
		HWND winHwnd = nullptr;
	public:
		DELETE_MOVE_COPY_CONSTRUCT(ClipMonitor);
		// 启动
		void Start(const Window& window, Call callback) noexcept;
		// 停止
		void Stop() noexcept;
	};
}

namespace winui {
	// 缓动特效
	class Gradient {
	public:
		class Mode final {
			Mode() = delete;
		public:
#define GMODE(name, value, comment) static constexpr Attr name = value
			GMODE(Power2In, 1, "二次方渐入"); GMODE(Power2Out, 2, "二次方渐出");
			GMODE(Power2InOut, 3, "二次方渐入渐出"); GMODE(Power3In, 4, "三次方渐入");
			GMODE(Power3Out, 5, "三次方渐出"); GMODE(Power3InOut, 6, "三次方渐入渐出");
			GMODE(Power4In, 7, "四次方渐入"); GMODE(Power4Out, 8, "四次方渐出");
			GMODE(Power4InOut, 9, "四次方渐入渐出"); GMODE(Power5In, 10, "五次方渐入");
			GMODE(Power5Out, 11, "五次方渐出"); GMODE(Power5InOut, 12, "五次方渐入渐出");
			GMODE(SinIn, 13, "正弦渐入"); GMODE(SinOut, 14, "正弦渐出");
			GMODE(SinInOut, 15, "正弦渐入渐出"); GMODE(ExpIn, 16, "指数渐入");
			GMODE(ExpOut, 17, "指数渐出"); GMODE(ExpInOut, 18, "指数渐入渐出");
			GMODE(CircleIn, 19, "圆曲线渐入"); GMODE(CircleOut, 20, "圆曲线渐出");
			GMODE(CircleInOut, 21, "圆曲线渐入渐出"); GMODE(ExpSinIn, 22, "指数衰减的正弦渐入");
			GMODE(ExpSinOut, 23, "指数衰减的正弦渐出"); GMODE(ExpSinInOut, 24, "指数衰减的正弦渐入渐出");
			GMODE(MorePower3In, 25, "超范围三次方渐入"); GMODE(MorePower3Out, 26, "超范围三次方渐出");
			GMODE(MorePower3InOut, 27, "超范围三次方渐入渐出"); GMODE(ExpReboundIn, 28, "指数衰减的反弹渐入");
			GMODE(ExpReboundOut, 29, "指数衰减的反弹渐出"); GMODE(ExpReboundInOut, 30, "指数衰减的反弹渐入渐出");
			GMODE(CircleLinear, 31, "圆线性插值缓动"); GMODE(Rebound, 32, "弹性缓动");
			GMODE(Lash, 33, "冲击缓动"); GMODE(Linear, 34, "线性缓动");
#undef GMODE
		};
		struct Data final { int start, end; Attr mode; };
		struct Task final {
			std::vector<Data> tasks;
		public:
			constexpr Task() noexcept = default;
			constexpr Task& Add(int start = 0, int end = 0, Attr mode = Mode::CircleInOut) noexcept {
				tasks.push_back({ start, end, mode });
				return *this;
			}
			constexpr std::vector<Data>& Tasks() noexcept { return tasks; }
			constexpr UINT Size() const noexcept { return tasks.size(); }
		};
	public:
		// 启动
		static void Start(Call callback, const Task& tasks, int step = 10, bool sync = false, int extraData = 0);
	};
}

#undef DELETE_MOVE_COPY_CONSTRUCT