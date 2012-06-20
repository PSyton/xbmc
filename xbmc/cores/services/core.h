#pragma once

namespace services {

class Core {

public:
  Core();
  virtual ~Core();
  virtual bool isValid() const;
};

} // namespace services
