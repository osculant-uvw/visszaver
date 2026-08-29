CREATE TABLE satellite_telemetry_timeseries (
    timestamp timestamptz NOT NULL DEFAULT now(),
    name text NOT NULL,
    pos_x numeric NOT NULL,
    pos_y numeric NOT NULL,
    pos_z numeric NOT NULL,
    vel_x numeric NOT NULL,
    vel_y numeric NOT NULL,
    vel_z numeric NOT NULL,
    acc_x numeric NOT NULL,
    acc_y numeric NOT NULL,
    acc_z numeric NOT NULL,
    PRIMARY KEY (timestamp, name)
)
