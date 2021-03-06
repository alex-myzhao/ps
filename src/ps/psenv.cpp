#include "ps/psenv.hpp"

namespace ps {

// initialize static variable
Psenv* Psenv::env_ = NULL;

Psenv::Psenv(int root, int count, bool debug) {
  MPI_Comm_size(MPI_COMM_WORLD, &size_);
  root_ = root > 0 ? root : 0;
  count_ = count;
  debug_ = debug;
}

bool Psenv::isServer() const {
  return root_ == Psenv::getCurRank();
}

void Psenv::setDebug(bool debug) {
  debug_ = debug;
}

Worker* Psenv::getWorker() {
  if (isServer()) return NULL;
  if (worker_ == NULL) {
    worker_ = new Worker(Psenv::getCurRank(), size_, root_, count_, debug_);
    if (debug_) printf("[PSENV]: WORKER of rank %d created\n", Psenv::getCurRank());
  }
  return worker_;
}

Server* Psenv::getServer() {
  if (!isServer()) return NULL;
  if (server_ == NULL) {
    server_ = new Server(Psenv::getCurRank(), size_, root_, count_, debug_);
    if (debug_) printf("[PSENV]: SERVER of rank %d created\n", Psenv::getCurRank());
  }
  return server_;
}

}
