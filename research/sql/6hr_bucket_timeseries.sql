WITH snapshots AS (
    SELECT
        *,
        MIN(timestamp) OVER (PARTITION BY name) AS first_timestamp
    FROM satellite_telemetry_timeseries
),
     six_hour_snapshots AS (
         SELECT
             *,
             timestamp - first_timestamp AS timedelta
         FROM snapshots
         WHERE MOD(EXTRACT(EPOCH FROM (timestamp - first_timestamp))::bigint, 6 * 60 * 60) = 0
     )
SELECT
    timedelta,
    name,
    pos_x, pos_y, pos_z,
    vel_x, vel_y, vel_z,
    acc_x, acc_y, acc_z
FROM six_hour_snapshots
ORDER BY timedelta, name;
