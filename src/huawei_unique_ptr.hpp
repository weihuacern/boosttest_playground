#include <algorithm>

namespace huawei {
    template<typename T>
    class unique_ptr {
        T* data;
    public:
        unique_ptr() : data(nullptr) {}
        explicit unique_ptr(T* data) : data(data) {}
        ~unique_ptr(){ delete data; }

        unique_ptr(unique_ptr const&) = delete;
        unique_ptr& operator=(unique_ptr const&) = delete;

        T* operator->() const { return data; }
        T& operator*() const { return *data; }

        T* get() const { return data; }
        explicit operator bool() const { return data; }

        T* release() {
            T* res = nullptr;
            std::swap(res, data);
            return res;
        }

        void swap(unique_ptr& src) noexcept {
            std::swap(data, src.data);
        }

        void reset() {
            T* tmp = release();
            delete tmp;
        }
    };
}
