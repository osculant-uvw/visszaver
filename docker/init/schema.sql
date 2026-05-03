CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TYPE order_side AS ENUM (
    'BUY',
    'SELL'
);

CREATE TYPE order_status AS ENUM (
    'OPEN',
    'FILLED',
    'REJECTED',
    'CANCELLED',
    'EXPIRED'
);

CREATE TABLE accounts (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    name TEXT NOT NULL
);

CREATE TABLE symbols (
   symbol TEXT PRIMARY KEY
);

CREATE TABLE orders (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    account_id UUID NOT NULL REFERENCES accounts(id),
    symbol TEXT NOT NULL REFERENCES symbols(symbol),
    side order_side NOT NULL,
    quantity NUMERIC NOT NULL CHECK (quantity > 0),
    price NUMERIC NOT NULL CHECK (price > 0),
    status order_status NOT NULL,
    submitted_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    updated_at TIMESTAMPTZ NOT NULL DEFAULT NOW()
);

CREATE INDEX idx_orders_account_id_created_at
    ON orders(account_id, submitted_at DESC);
