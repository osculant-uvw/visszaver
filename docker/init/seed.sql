-- Accounts
INSERT INTO accounts (id, name) VALUES
    ('a3f1c7b2-9d44-4e92-8fcb-1c7a8d12e001', 'Alpha Fund'),
    ('b7d2e891-6c55-4a11-9aa3-3f6d5e44b002', 'Beta Fund');

-- Symbols
INSERT INTO symbols (symbol) VALUES
     ('AAPL'),
     ('MSFT'),
     ('GOOG'),
     ('NVDA'),
     ('AMZN'),
     ('TSLA'),
     ('META'),
     ('SPY'),
     ('QQQ'),
     ('AMD');

-- Orders
INSERT INTO orders (
    id,
    account_id,
    symbol,
    side,
    quantity,
    price,
    status,
    submitted_at,
    updated_at
) VALUES

-- Alpha Fund
('d1019c3a-2e55-4d4e-baa1-001a9f000001', 'a3f1c7b2-9d44-4e92-8fcb-1c7a8d12e001', 'AAPL', 'BUY', 100, 175.50, 'FILLED', NOW() - INTERVAL '5 hours', NOW() - INTERVAL '4 hours 50 minutes'),
('d1019c3a-2e55-4d4e-baa1-001a9f000002', 'a3f1c7b2-9d44-4e92-8fcb-1c7a8d12e001', 'MSFT', 'SELL', 50, 410.00, 'OPEN', NOW() - INTERVAL '4 hours', NOW() - INTERVAL '4 hours'),
('d1019c3a-2e55-4d4e-baa1-001a9f000003', 'a3f1c7b2-9d44-4e92-8fcb-1c7a8d12e001', 'NVDA', 'BUY', 25, 880.00, 'FILLED', NOW() - INTERVAL '3 hours', NOW() - INTERVAL '2 hours 55 minutes'),
('d1019c3a-2e55-4d4e-baa1-001a9f000004', 'a3f1c7b2-9d44-4e92-8fcb-1c7a8d12e001', 'SPY', 'BUY', 200, 510.00, 'FILLED', NOW() - INTERVAL '2 hours', NOW() - INTERVAL '1 hour 55 minutes'),
('d1019c3a-2e55-4d4e-baa1-001a9f000005', 'a3f1c7b2-9d44-4e92-8fcb-1c7a8d12e001', 'AMD', 'SELL', 150, 165.00, 'CANCELLED', NOW() - INTERVAL '1 hour', NOW() - INTERVAL '50 minutes'),

-- Beta Fund
('e2028d4b-7f66-4c9a-bbb2-002b8e000001', 'b7d2e891-6c55-4a11-9aa3-3f6d5e44b002', 'TSLA', 'SELL', 75, 185.00, 'FILLED', NOW() - INTERVAL '6 hours', NOW() - INTERVAL '5 hours 55 minutes'),
('e2028d4b-7f66-4c9a-bbb2-002b8e000002', 'b7d2e891-6c55-4a11-9aa3-3f6d5e44b002', 'AMZN', 'BUY', 40, 182.00, 'EXPIRED', NOW() - INTERVAL '5 hours', NOW() - INTERVAL '4 hours 45 minutes'),
('e2028d4b-7f66-4c9a-bbb2-002b8e000003', 'b7d2e891-6c55-4a11-9aa3-3f6d5e44b002', 'META', 'BUY', 60, 470.00, 'OPEN', NOW() - INTERVAL '4 hours', NOW() - INTERVAL '4 hours'),
('e2028d4b-7f66-4c9a-bbb2-002b8e000004', 'b7d2e891-6c55-4a11-9aa3-3f6d5e44b002', 'QQQ', 'SELL', 120, 445.00, 'FILLED', NOW() - INTERVAL '2 hours', NOW() - INTERVAL '1 hour 50 minutes'),
('e2028d4b-7f66-4c9a-bbb2-002b8e000005', 'b7d2e891-6c55-4a11-9aa3-3f6d5e44b002', 'AAPL', 'BUY', 90, 176.25, 'FILLED', NOW() - INTERVAL '1 hour', NOW() - INTERVAL '55 minutes');
