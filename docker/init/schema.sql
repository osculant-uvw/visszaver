CREATE TABLE telemetry_timeseries (
    satellite_id text NOT NULL,
    received_at timestamptz NOT NULL DEFAULT now(),
    latitude_degrees numeric NOT NULL,
    longitude_degrees numeric NOT NULL,
    altitude_metres numeric NOT NULL,
    speed_metres_per_second numeric NOT NULL,
    temperature_kelvin numeric NOT NULL,
    PRIMARY KEY (satellite_id, received_at)
)
