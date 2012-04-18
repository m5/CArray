require './carray'

class CArray
  include CArrayExt
  def initialize a
    @bin = "\x00" * 4 * a.size
    @bin = native_fill_array(@bin, a)
  end

  def max_index
    native_max_index(@bin) 
  end

  def [] idx
    native_get_index(@bin, idx)
  end

  def []= idx, val
    native_set_index(@bin, idx, val)
  end
end
