#ifndef THING_MODULE_H
#define THING_MODULE_H


// #define THING "FirstTestDevice"
#define THING "tulio_master"

#define CA_CERT "-----BEGIN CERTIFICATE-----\n" \
                "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
                "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
                "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
                "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
                "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
                "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
                "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
                "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
                "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
                "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
                "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
                "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
                "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
                "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
                "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
                "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
                "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
                "rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
                "-----END CERTIFICATE-----\n"

#define CLIENT_CERT "-----BEGIN CERTIFICATE-----\n" \
                    "MIIDWTCCAkGgAwIBAgIUb4ZMCMLuzh499wz/hatJkWBLdu8wDQYJKoZIhvcNAQEL\n" \
                    "BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n" \
                    "SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MTAyMDE3NDQx\n" \
                    "MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n" \
                    "ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANBP8CPTubIhU6qDzgEy\n" \
                    "sI8LKIr57F76USdogOUurWF771GJeuPG3XSFf7xiE7WZlT1mbzlHYKbr8RllJ8E1\n" \
                    "i2KjeIXJN6mrseDEcBmjrbvCoaqPfjtsoxHZH8bRNj3iQTDC9BoyAxcvNm563vWc\n" \
                    "xPxoHaOKyowJ6B/7aleisNfo+qmwbqANakyQlA7BX3GGfL8Wu0h77EM1QmSmn+QJ\n" \
                    "H9If2PZQLMRsRgwWhPBbrI6ZTWJQCmHp1G7Ijt6PYXnQAlh2n9eFDtjRlKs0+XAR\n" \
                    "QtnZBo6oeO8IgtU/oHntJSQFV879JLsLrt6HpngMJgI6AfqkeRm42a0WHS6GOZPp\n" \
                    "qfsCAwEAAaNgMF4wHwYDVR0jBBgwFoAUdIlostNYXcoyolEnrO6Xvxnd9+swHQYD\n" \
                    "VR0OBBYEFDXy7Y/1G92Z8RyYDJnJCp/PTrl/MAwGA1UdEwEB/wQCMAAwDgYDVR0P\n" \
                    "AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQA82O8mgdcjt6fi5tHfoYb29ltE\n" \
                    "A+5hDN4fVjTZd65KrysdXvNnynlYwAUGYkr2GaKd8rknePlRCIsO6Xu0EoPfSlP+\n" \
                    "7tH0DKow5Zi6Rs5ncVCFbtLtFQdfmzjYZx6rdYV2+f5MrLJGRGYhei/SbdKw4aWK\n" \
                    "3neR5/6iVoEnX9PqZqi0mcgRUymB3kUeSskTMuVtmmjjO7S5o3OSInv2jT0e8GpK\n" \
                    "Uw/BQ0yktsNY1vu/M+CC/4X5TmGtF7JJ95AgAqdSPF5dWOuXOVmkJszunwHEwb5U\n" \
                    "3J+j+hg4kHund+lvaYoQsgVre9qUnlRejgyZBi4GUWuvEHuKllIFtQAGPxf+\n" \
                    "-----END CERTIFICATE-----\n"


#define CLIENT_KEY "-----BEGIN RSA PRIVATE KEY-----\n" \
                   "MIIEpAIBAAKCAQEA0E/wI9O5siFTqoPOATKwjwsoivnsXvpRJ2iA5S6tYXvvUYl6\n" \
                   "48bddIV/vGITtZmVPWZvOUdgpuvxGWUnwTWLYqN4hck3qaux4MRwGaOtu8Khqo9+\n" \
                   "O2yjEdkfxtE2PeJBMML0GjIDFy82bnre9ZzE/Ggdo4rKjAnoH/tqV6Kw1+j6qbBu\n" \
                   "oA1qTJCUDsFfcYZ8vxa7SHvsQzVCZKaf5Akf0h/Y9lAsxGxGDBaE8FusjplNYlAK\n" \
                   "YenUbsiO3o9hedACWHaf14UO2NGUqzT5cBFC2dkGjqh47wiC1T+gee0lJAVXzv0k\n" \
                   "uwuu3oemeAwmAjoB+qR5GbjZrRYdLoY5k+mp+wIDAQABAoIBAFTws4e4VpjW1AnM\n" \
                   "cty0MaAyOZbpr8NOqHa8Owq4jMQaSAxkVbK5LSXNJbfH+idrd5owwZuGilemD4p+\n" \
                   "X8Z9sddHtuY+lS7fLsnq75bU0gukok0s85kBhEDL2xQzzL1RG6npZKWlzPLQMo68\n" \
                   "FVvrT7toLOW5uzt88qTP3J3dXeS7g9F36swXQLvXJ57Ln5eW9Lt77JXw1XfKwAgk\n" \
                   "m4G4/brMXKwtryBAQZfekoau3hdTo1oqjkZ2dACRJgYxw4uM9KUrzmsTeZuJCn1v\n" \
                   "LbkLRPTgxe4G8xuG7+ze+y8HOS598p1SiBjUMm/gmoxDP0iUcsCyhRGWk/M8W4Vc\n" \
                   "pJjHYzkCgYEA7GOZ4DgTwNni43woEY1OB/SH4Z88P55CZ168UaGFxQtq0ej7XcPw\n" \
                   "I+/9aP8Y6zu+8qXwmPDz7WDxE1YYwKWJ92l0AZLIbqojpmLg0jEQ5EkpcA7jCsWO\n" \
                   "OC7oS5Q/9s41/aWGKcpEfJxUSg+j8sBpkKnnlO6gS4Hj1N5j58WJGTcCgYEA4ZgL\n" \
                   "pubKqk8q2EznW0DSpiRXxBRHhqA2016xwnzoFNsD7nmM6hMuUX10o9ana+Ynasin\n" \
                   "q5mNeBdriDkT8xjhCpjdW11UP2XcukniQgxTFzRA23TGWUOVBj4V4dWlSQbyuDuP\n" \
                   "PePaKWWHyIkw4aYUHteA2245hhNb6KveSNNtB10CgYB85edQm/B77eO+dEQrefCn\n" \
                   "rWD6KgtIRdMqENkJfIFUakLnY+UkVrmUE2JeTqKY73lldZ3ZAT6wxo65u7zaVNy/\n" \
                   "t50Ok8KJDiZF7GqDRF97btiRF5yIfXc2YjpkbJEbUzsdqI5pmDB1cpfqhbcHNPjR\n" \
                   "8aOlgit5mciKGXLJ7AoTIwKBgQDK5/jC+56ZpG9C8Zi+CQXujY2rPRpASmZFo0x7\n" \
                   "Q+FysLNOkWFfQDVO8mow2ubnM7GMaEH3JDuMInSDp+L7qgrvfyLKBJ28ECCCJeYt\n" \
                   "xewOWN9lBBlLPHATl1ATOhhaILe7YUarQf99cGa6xjqDGt/KBcdOlkuC/nKSSdO6\n" \
                   "6P+NuQKBgQDCQ9s8fXwdIhnFdBoUt8h3TgXnvvqFJrO+YQTiLalb6LoNb14XNtGz\n" \
                   "Ywhy3sSuN325oqIAyE9Vflij6T57ceIwD3rjQoBtH0G5tRVey5CCF8qw/Umfes9S\n" \
                   "22et8vsmMggfz70DldhCnmT65iess4kaS2rass1VaT+4fQQCfBAxoQ==\n" \
                   "-----END RSA PRIVATE KEY-----\n"
// variaveis


#endif