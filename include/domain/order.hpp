#pragma once

#include <chrono>
#include <stdexcept>
#include <string>
#include <utility>


namespace domain {

enum class OrderSide {
    BUY,
    SELL
};


enum class OrderStatus {
    OPEN,
    FILLED,
    REJECTED,
    CANCELLED,
    EXPIRED
};


class Order {
public:

    static Order create(
            std::string id,
            std::string accountId,
            std::string symbol,
            OrderSide side,
            double quantity,
            double price
    ) {
        if (quantity <= 0.0) {
            throw std::invalid_argument("Order quantity must be positive");
        }
        if (price <= 0.0) {
            throw std::invalid_argument("Order price must be positive");
        }
        if (symbol.empty()) {
            throw std::invalid_argument("Symbol cannot be empty");
        }

        auto now = std::chrono::system_clock::now();

        return Order{
                std::move(id),
                std::move(accountId),
                std::move(symbol),
                side,
                quantity,
                price,
                OrderStatus::OPEN,
                now,
                now
        };
    }

    const std::string id;
    const std::string accountId;
    const std::string symbol;
    const OrderSide side;
    const double quantity;
    const double price;
    const std::chrono::system_clock::time_point submittedAt;
    OrderStatus status;
    std::chrono::system_clock::time_point updatedAt;

private:
    Order(
            std::string id,
            std::string accountId,
            std::string symbol,
            OrderSide side,
            double quantity,
            double price,
            OrderStatus status,
            std::chrono::system_clock::time_point submittedAt,
            std::chrono::system_clock::time_point updatedAt
    )
            : id(std::move(id)),
              accountId(std::move(accountId)),
              symbol(std::move(symbol)),
              side(side),
              quantity(quantity),
              price(price),
              submittedAt(submittedAt),
              status(status),
              updatedAt(updatedAt)
    {}
};

}
