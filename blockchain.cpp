#include <iostream>
#include <time.h>
#include "blockchain.hpp"
//#include <cpr/cpr.h>

using namespace blockchain;

Transaction::Transaction(std::string sender, std::string receiver,
    uint64_t amount)
  : sender_{sender}, receiver_{receiver}, amount_{amount} {}

Block::Block(uint64_t index, uint64_t timestamp, uint64_t proof,
    uint64_t previous_hash, Transaction_list transactions)
  : index_{index}, timestamp_{timestamp}, proof_{proof},
  previous_hash_{previous_hash}, transactions_{transactions} {}

BlockChain::BlockChain()
  : chain_{}, current_transactions_{}, nodes_{}
{
  new_block(100, 1);
}

/* Assume url is valid */
void BlockChain::register_node(std::string url)
{
  nodes_.insert(url);
}

bool BlockChain::resolve_conflicts()
{
  list<Block> new_chain;
  auto neighbours = nodes_;
  auto max_len = nodes_.size();

  for (auto node = nodes_.begin(); node != nodes_.end();) {
    /*
    auto req = "http://" + node + "/chain";
    auto r = cpr::Get(cpr::Url{req});
    if (r.status_code == 200) {
      std::cout << r.text << std::endl;
    }
    */
  }
  return true;
}

Block& BlockChain::new_block(uint64_t proof, uint64_t previous_hash)
{
  chain_.emplace_back(chain_.size() + 1, time(0), proof,
      previous_hash /* or something is there */,
      current_transactions_);
  current_transactions_.clear();

  return last_block();
}

uint64_t BlockChain::new_transaction(std::string sender, std::string receiver,
    uint64_t amount)
{
  current_transactions_.emplace_back(sender, receiver, amount);
  return  last_block().index() + 1;
}

uint64_t BlockChain::hash( Block &block)
{
  return 10;
}

bool BlockChain::valid_proof(uint64_t last_proof, uint64_t proof,
    uint64_t last_hash)
{
  return false;
}

uint64_t BlockChain::proof_of_work()
{
  auto last_proof = last_block().proof();
  auto last_hash = hash(last_block());

  auto proof = 0;
  while (valid_proof(last_proof, proof, last_hash) == false) {
    proof += 1;
  }
  return proof;
}

int main()
{
  std::cout << "Hello Blockchain\n";
}
