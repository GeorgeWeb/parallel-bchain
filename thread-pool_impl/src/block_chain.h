#pragma once

#include "../include/tpool/tpool.hpp"

#include <string>
#include <vector>

class block final {
  public:
    block(uint32_t index, const std::string &data);

    // Difficulty is the minimum number of zeros we require at the
    // start of the hash.
    void mine_block(uint32_t difficulty) noexcept;

    inline const std::string& get_hash() const noexcept { 
        return _hash; 
    }

    // Hash code of the previous block in the chain.
    std::string prev_hash;

 private:
    // The index of the block in the chain.
    uint32_t _index;
    
    // A modifier used to get a suitable block.
    mutable std::shared_ptr<std::atomic<uint64_t>> _nonce;
    // A flag to check for successful hash calculation.
    mutable std::shared_ptr<std::atomic<bool>> _modified_hash;
    
    // Data stored in the block.
    std::string _data;
    // Hash code of this block.
    std::string _hash;
    // Time code block was created.
    long _time;

    std::string calculate_hash() const noexcept;
};

class block_chain final {
 private:
    uint32_t _difficulty;
    std::vector<block> _chain;

    inline const block& get_last_block() const noexcept { return _chain.back(); }

 public:
    block_chain();

    void add_block(block new_block) noexcept;
};