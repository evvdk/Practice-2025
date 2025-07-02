wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2404/x86_64/cuda-keyring_1.1-1_all.deb
sudo dpkg -i cuda-keyring_1.1-1_all.deb
sudo rm cuda-keyring_1.1-1_all.deb

sudo apt-get update
sudo apt-get -y install cudnn

sudo apt -y install python3-pip python3-requests python3-venv

python3 -m venv .venv
source .venv/bin/activate

python3 -m pip install --upgrade pip
pip install -r requirements.txt