FROM gcc:11.3.0
WORKDIR /app
COPY . /app
RUN make
ENTRYPOINT ["bash"]
CMD ["start.sh"]