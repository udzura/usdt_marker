require_relative 'lib/usdt_marker/version'

Gem::Specification.new do |spec|
  spec.name          = "usdt_marker"
  spec.version       = UsdtMarker::VERSION
  spec.authors       = ["Uchio Kondo"]
  spec.email         = ["udzura@udzura.jp"]

  spec.summary       = %q{Event marker using USDT}
  spec.description   = %q{Event marker using USDT. You can trace those user-defined events from eBPF.}
  spec.homepage      = "https://github.com/udzura/usdt_marker"
  spec.required_ruby_version = Gem::Requirement.new(">= 2.3.0")

  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions    = ["ext/usdt_marker/extconf.rb"]

  spec.add_development_dependency "bundler", ">= 1.6"
end
