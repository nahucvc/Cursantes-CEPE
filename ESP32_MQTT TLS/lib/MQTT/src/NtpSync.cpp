#include "NtpSync.h"
#include <WiFi.h>
#include <time.h>
#include <lwip/apps/sntp.h>

static const time_t TIME_OK_THRESHOLD = 1700000000;

static bool waitForTime(uint32_t timeoutMs = 20000) {
  time_t now = 0;
  uint32_t t0 = millis();
  do {
    time(&now);
    if (now > TIME_OK_THRESHOLD) return true;
    delay(200);
  } while (millis() - t0 < timeoutMs);
  return false;
}

void syncTime() {
  Serial.println("[NTP] Iniciando sincronización...");

  IPAddress ip;
  bool dnsOK = (WiFi.hostByName("pool.ntp.org", ip) == 1);
  if (dnsOK) Serial.printf("[NTP] pool.ntp.org -> %s\n", ip.toString().c_str());

  const char* s0 = dnsOK ? "pool.ntp.org" : "216.239.35.0";
  const char* s1 = "216.239.35.4";
  const char* s2 = "216.239.35.8";
  const char* s3 = "216.239.35.12";

  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, (char*)s0);
  sntp_setservername(1, (char*)s1);
  sntp_setservername(2, (char*)s2);
  sntp_setservername(3, (char*)s3);
  sntp_init();

  if (!waitForTime(20000)) {
    Serial.println("[NTP] No se pudo sincronizar (¿UDP/123 bloqueado?).");
  } else {
    time_t now = time(nullptr);
    Serial.printf("[NTP] Hora (UTC): %s", ctime(&now));
  }

  setenv("TZ", "ART-3", 1);
  tzset();

  time_t nowLocal = time(nullptr);
  struct tm lt;
  localtime_r(&nowLocal, &lt);
  char buf[64];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %Z", &lt);
  Serial.printf("[NTP] Hora local: %s\n", buf);
}
