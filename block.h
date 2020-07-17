#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include <memory>
#include <stdexcept>

namespace my
{

template <std::size_t n>
class Block
{
public:
    Block()
        : m_bytes(std::make_unique<std::array<bool, n>>())
    {
    }

    Block(const Block& other)
        : m_bytes(std::make_unique<std::array<bool, n>>(*other.m_bytes))
    {
    }
    Block& operator=(const Block& other)
    {
        m_bytes = std::make_unique<std::array<bool, n>>(*other.m_bytes);
    }

    Block(Block&&) noexcept = default;
    Block& operator=(Block&&) noexcept = default;

    static constexpr std::size_t size() noexcept
    {
        return n;
    }

    bool operator[](std::size_t index) const
    {
        return (*m_bytes)[index];
    }

    bool at(std::size_t index) const
    {
        m_bytes->at(index);
    }

    bool& operator[](std::size_t index)
    {
        return (*m_bytes)[index];
    }

    bool& at(std::size_t index)
    {
        return m_bytes->at(index);
    }

private:
    using StorageType = std::unique_ptr<std::array<bool, n>>;
    StorageType m_bytes;

public:
    using Iterator = typename StorageType::element_type::iterator;
    using ConstIterator = typename StorageType::element_type::const_iterator;

    constexpr Iterator begin() noexcept
    {
        return m_bytes->begin();
    }
    constexpr ConstIterator begin() const noexcept
    {
        return m_bytes->begin();
    }
    constexpr ConstIterator cbegin() const noexcept
    {
        return m_bytes->cbegin();
    }
    constexpr Iterator end() noexcept
    {
        return m_bytes->end();
    }
    constexpr ConstIterator end() const noexcept
    {
        return m_bytes->end();
    }
    constexpr ConstIterator cend() const noexcept
    {
        return m_bytes->cend();
    }
};

} // namespace my

#endif // BLOCK_H
