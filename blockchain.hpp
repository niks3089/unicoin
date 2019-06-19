#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <set>
#include <list>

using namespace std;

namespace blockchain {

class Transaction {
  public:
    Transaction(std::string, std::string, uint64_t);
    std::string sender()   { return sender_; }
    std::string receiver() { return receiver_; }
    uint64_t    amount()   { return amount_; }

  private:
  std::string sender_;
  std::string receiver_;
  uint64_t    amount_;
};

class Block {
  public:
  using Transaction_list = std::list<Transaction>;
  Block(uint64_t index, uint64_t timestamp, uint64_t proof,
      uint64_t previous_hash, Transaction_list transactions);

  uint64_t index() { return index_; }
  uint64_t proof() { return proof_; }
  uint64_t previous_hash() { return previous_hash_; }

  private:
    uint64_t         index_;
    uint64_t         timestamp_;
    uint64_t         proof_;
    uint64_t         previous_hash_;
    Transaction_list transactions_;
};

class BlockChain {

  public:
  using Block_list       = std::list<Block>;
  using Transaction_list = std::list<Transaction>;
  using Node_set         = std::set<string>;

  BlockChain();
  Block& new_block(uint64_t proof, uint64_t previous_hash);
  uint64_t new_transaction(std::string sender, std::string receiver,
    uint64_t amount);
  void register_node(std::string address);
  bool resolve_conflicts();
  uint64_t proof_of_work();

private:
  Block_list       chain_;
  Transaction_list current_transactions_;
  Node_set         nodes_;

  uint64_t hash(Block &block);
  bool valid_proof(uint64_t last_proof, uint64_t proof,
      uint64_t last_hash);
  void vaild_chain();
  Block& last_block() { return chain_.back(); }
};

}
#endif
