<?hh // strict
namespace Fastuc\Feed\Rss;

class Item
{
	private string $title;
	private string $link;
	private string $description;
	private string $pubDate;

	public function setTitle( string $title ) : void
	{
		$this->title = $title;
	}

	public function getTitle() : string
	{
		return $this->title;
	}

	public function setLink( string $link ) : void
	{
		$this->link = $link;
	}

	public function getLink() : string
	{
		return $this->link;
	}

	public function setDescription( string $description ) : void
	{
		$this->description = $description;
	}

	public function getDescription() : string
	{
		return $this->description;
	}

	public function setPubDate( string $pubDate ) : void
	{
		$this->pubDate = $pubDate;
	}

	public function getPubDate() : ?string
	{
		return $this->pubDate;
	}
}

