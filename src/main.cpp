#include <store.h>

void server(KeyValueStore& kv);


int main(){
    KeyValueStore kv;
    server(kv);
}