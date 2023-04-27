#include "WalletDecorator.h"
#include "IEntity.h"

WalletDecorator::WalletDecorator(IEntity* entity){
    this->entity = entity;
}

int WalletDecorator::GetCapacity() {
    return this->capacity;
}
