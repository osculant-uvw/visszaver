## Local development

Run Postgres with docker compose:

```bash
cd docker
docker compose up -d
```

To reset the database: 

```bash
docker compose down -v
docker compose up -d
```
