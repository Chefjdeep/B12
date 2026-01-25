import requests
try:
    response = requests.get('http://10.208.53.231:5000', timeout=5)
    print(f"Success! Status: {response.status_code}")
except Exception as e:
    print(f"Failed: {e}")