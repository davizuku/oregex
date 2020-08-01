#!/bin/bash

cd /oregex
ln -s /vendor vendor
chown -R vendor --reference=test
