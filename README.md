# UsdtMarker

[![Gem Version](https://badge.fury.io/rb/usdt_marker.svg)](https://badge.fury.io/rb/usdt_marker)

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'usdt_marker'
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install usdt_marker

### Limitations

* This is tested only against Linux system; My environment uses kernel 5.0.0 :)
  * Extention requires a package named `systemtap-sdt-dev` or something alike
* I know some of UNIX systems also has `<sys/sdt.h>` header file, but I'm not going to test.
  * Your supports are welcomed!

## Usage

Very simple tutorial.

Install those tools to your system:

* package `systemtap-sdt-dev` or something alike.
* `bpftrace`. We recommend via OS package, binary or self-build, because snap version of bpftrace cannot recognize uprobe/usdt for now.
* Ruby. Some systems may require `ruby-dev` package.

Then invoke your irb, e.g. in the bundle environment with usdt_marker.

```ruby
irb(main):001:0> require 'usdt_marker'
irb(main):002:0> puts $$
19644
```

On another terminal, hit `bpftrace` to find the name of USDT; USDT may be defined in gem's shared object:

```console
$ sudo bpftrace -p 19644 -l 'usdt:*' | grep ruby
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:array__create
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:raise
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:gc__sweep__end
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:gc__sweep__begin
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:gc__mark__end
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:gc__mark__begin
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:hash__create
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:load__entry
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:load__return
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:find__require__return
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:require__entry
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:find__require__entry
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:require__return
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:object__create
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:parse__begin
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:parse__end
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:string__create
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:symbol__create
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:method__cache__clear
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:cmethod__entry
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:cmethod__return
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:method__return
usdt:/root/.rbenv/versions/2.6.5/lib/libruby.so.2.6.5:ruby:method__entry
usdt:/usr/local/ghq/github.com/udzura/usdt_marker/lib/usdt_marker/usdt_marker.so:rubygem:usdt_marker_i1s1
usdt:/usr/local/ghq/github.com/udzura/usdt_marker/lib/usdt_marker/usdt_marker.so:rubygem:usdt_marker_i2
```

Then start tracing:

```
$ sudo bpftrace -p 19644 -e \
  'usdt:/usr/local/ghq/github.com/udzura/usdt_marker/lib/usdt_marker/usdt_marker.so:rubygem:usdt_marker_i1s1 {
    printf("Fire!: %d, %s\n", arg0, str(arg1));
  }'
Attaching 1 probe...
```

Return to irb, hit probe methods:

```ruby
irb(main):003:0> UsdtMarker.probe_i1s1(2020, "hello, world!")
=> true
irb(main):004:0> UsdtMarker.probe_i1s1(2020, "hello, world! again")
=> true
```

After all bpftrace process traces these events:

```
...
Fire!: 2020, hello, world!
Fire!: 2020, hello, world! again
```

Method-USDT counterparts:

* `UsdtMarker.probe_i1s1(<Integer>, <String>)` - `rubygem:usdt_marker_i1s1`
* `UsdtMarker.probe_i2(<Integer>, <Integer>)` - `rubygem:usdt_marker_i2`

## Development

After checking out the repo, run `bin/setup` to install dependencies. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/udzura/usdt_marker.

