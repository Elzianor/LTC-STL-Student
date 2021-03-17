#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class StaticPlaylist
{
public:
    /** @todo Member traits */
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using difference_type = typename Container::difference_type;
    using pointer = typename Container::pointer;
    using const_pointer = typename Container::const_pointer;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using reverse_iterator = typename Container::reverse_iterator;
    using const_reverse_iterator = typename Container::const_reverse_iterator;

    /** @todo Iterators */
    const_iterator begin()
    {
        return std::begin(m_tracklist);
    }

    const_iterator end()
    {
        return std::end(m_tracklist);
    }

    StaticPlaylist() = default;

    /** @todo Constructor from any reversible sequence container */
    template <class OtherContainer>
    StaticPlaylist(const OtherContainer& other)
        : m_tracklist(other.rbegin(), other.rend())
    {
    }

    /** @todo Assignment from any reversible sequence container */
    template <class OtherContainer>
    StaticPlaylist& operator=(const OtherContainer& other)
    {
        m_tracklist.assign(other.rbegin(), other.rend());
        return *this;
    }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData)
    {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Add track */
    const Song_t& play(const Song_t& song)
    {
        m_tracklist.emplace_back(song);
        return current();
    }

    /** @todo Get first track in playlist stack */
    const Song_t& current() const
    {
        return m_tracklist.back();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if (m_tracklist.empty())
        {
            throw std::out_of_range("Track list is empty!");
        }

        m_tracklist.pop_back();
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const
    {
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const
    {
        return !m_tracklist.empty();
    }

private:
    Container m_tracklist;
};
